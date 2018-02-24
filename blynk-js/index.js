#!/usr/bin/env node

var AUTH = "f3b63e03dbaf40c7a6c377ddf9504387";
var SerialPort = require("serialport");

var port = new SerialPort("/dev/ttyS0", { baudRate: 115200 });

port.on('error', (err) => {
  console.log(err.message);
  process.exit(1);
});

var BlynkLib = require("blynk-library");

var blynk = new BlynkLib.Blynk(
  AUTH,
  (options = {
    connector: new BlynkLib.TcpClient(
      (options = { addr: "127.0.0.1", port: 8442 })
    )
  })
);

var pins = [];

const pinmap = [
  "fwd",
  "bkd",
  "left",
  "right",
  "slider",
  "power",
  "cw",
  "ccw",
  "dcv_r_up",
  "dcv_r_down",
  "belt_r_fwd",
  "belt_r_rev",
  "belt_l_fwd",
  "belt_l_rev",
  "dcv_l_up",
  "dcv_l_down"
];

var data = {};

pinmap.forEach(val => {
  data[val] = 0;
});

console.log(data);

function check_belt() {
  if (data["belt_l_fwd"] !== 0) data["belt_l"] = 1;
  else if (data["belt_l_rev"] !== 0) data["belt_l"] = 2;
  else data["belt_l"] = 0;

  if (data["belt_r_fwd"] !== 0) data["belt_r"] = 1;
  else if (data["belt_r_rev"] !== 0) data["belt_r"] = 2;
  else data["belt_r"] = 0;
}

function check_dcv() {
  if (data["dcv_l_up"]) data["dcv_l"] = 1;
  else if (data["dcv_l_down"]) data["dcv_l"] = 2;
  else data["dcv_l"] = 0;

  if (data["dcv_r_up"]) data["dcv_r"] = 1;
  else if (data["dcv_r_down"]) data["dcv_r"] = 2;
  else data["dcv_r"] = 0;
}

function send_data(point, name) {
  port.write(Buffer.from(point[0]));
  port.write(Buffer.from([data[name]]));
}

function mkzero() {
  Object.keys(data).forEach(key => {
    data[key] = 0
  });
}

function update_data() {
  port.write(Buffer.from("s"));
  send_data("f", "fwd");
  send_data("b", "bkd");
  send_data("l", "left");
  send_data("r", "right");
  send_data("p", "slider");
  send_data("o", "power");
  send_data("c", "cw");
  send_data("v", "dcv_l");
  send_data("w", "dcv_r");
  send_data("x", "belt_l");
  send_data("y", "belt_r");
  send_data("d", "ccw");
}

for (let i = 0; i < 16; i++) {
  var p = new blynk.VirtualPin(i);
  p.on("write", param => {
    var varname = pinmap[i];
    data[varname] = parseInt(param, 10);
  });
  pins.push(p);
}

blynk.on("connect", function() {
  console.log("Blynk ready.");
  blynk.syncAll();
  GLOBAL.handle = setInterval(() => update_data(), 100);
});

blynk.on("disconnect", function() {
  console.log("DISCONNECT");
  mkzero();
  update_data();
  clearInterval(GLOBAL.handle);
});


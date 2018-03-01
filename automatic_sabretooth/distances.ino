constexpr int MOTOR_DELAY = 200;

// startup
constexpr int SIDEWAYS_DELAY = 700;
constexpr int START_TO_A = 14200;

constexpr int A_TO_BLUE = 3417;
// end startup

//constexpr int BLUE_TO_TZ1 = 5012;
constexpr int BLUE_TO_TZ1 = 5012 - 820;

//constexpr int TZ1_TO_FENCE = 2172;  // 2100 ?
constexpr int TZ1_TO_FENCE = 2200;
constexpr int FENCE_SPEED = 160;

constexpr int FENCE_TO_TZ1 = 2065;
constexpr int TZ1_TO_BLUE = BLUE_TO_TZ1;

constexpr int TZ1BLUE_OFFSET = 3000;
constexpr int A_TO_B = 6300;

constexpr int OFFSET_TO_TZ2 = BLUE_TO_TZ1+TZ1BLUE_OFFSET;

constexpr int BLUE_TO_TZ3 = 15354 - 820 - 100;
constexpr int TZ3_TO_BLUE = BLUE_TO_TZ3;

constexpr int OFFSET_TO_A = 705;
constexpr int START_TO_LINE = 1832;



/* =========================================================================
      THREE STEPPER MOTORS CONTROL SYSTEM
      MANUAL DIRECTION + COORDINATE DISTANCE PARAMETERS
      Fully configurable like C macros
      Mechanism Assumption:
         Motor1 = X axis
         Motor2 = Y axis
         Motor3 = Z axis
   =========================================================================
*/

/* ========================== USER PARAMETERS ============================ */

// --- Target travel distance in millimeters (user changes these) ----------
#define X_TARGET_MM      10.0    // Move Motor 1 by 10 mm
#define Y_TARGET_MM      5.0     // Move Motor 2 by 5 mm
#define Z_TARGET_MM      3.0     // Move Motor 3 by 3 mm

// --- Manual direction control -------------------------------------------
// +1 = Clockwise (CW)
// -1 = Counter-Clockwise (CCW)
#define M1_DIR           1       // Motor 1 manual direction
#define M2_DIR          -1       // Motor 2 manual direction
#define M3_DIR           1       // Motor 3 manual direction

// --- Steps per millimeter (mechanical tuning) ---------------------------
// Example: 200 steps/rev, 8mm lead screw → 25 steps/mm
#define STEPS_PER_MM     25.0

// --- Motor Speed ---------------------------------------------------------
#define MOTOR_SPEED      3       // Delay in ms between steps (higher = slower)

// --- Continuous rotation mode -------------------------------------------
// 0 = move once and stop
// 1 = repeat motion forever
#define CONTINUOUS_MODE  0

/* ====================================================================== */
/* =================== INTERNAL MOTOR PIN DEFINITIONS ==================== */
/* ====================================================================== */

// Motor 1 (L298P)
#define M1_IN1 22
#define M1_IN2 23
#define M1_IN3 24
#define M1_IN4 25

// Motor 2 (L293D #1)
#define M2_IN1 26
#define M2_IN2 27
#define M2_IN3 28
#define M2_IN4 29

// Motor 3 (L293D #2)
#define M3_IN1 30
#define M3_IN2 31
#define M3_IN3 32
#define M3_IN4 33

/* ====================================================================== */
/* ======================  STEP SEQUENCE TABLE  ========================== */
/* ====================================================================== */

int seq[4][4] = {
  {1,0,1,0},  // Step 0
  {0,1,1,0},  // Step 1
  {0,1,0,1},  // Step 2
  {1,0,0,1}   // Step 3
};

/* ====================================================================== */
/* =========================   SETUP FUNCTION  =========================== */
/* ====================================================================== */

void setup() {
  pinMode(M1_IN1, OUTPUT); pinMode(M1_IN2, OUTPUT);
  pinMode(M1_IN3, OUTPUT); pinMode(M1_IN4, OUTPUT);

  pinMode(M2_IN1, OUTPUT); pinMode(M2_IN2, OUTPUT);
  pinMode(M2_IN3, OUTPUT); pinMode(M2_IN4, OUTPUT);

  pinMode(M3_IN1, OUTPUT); pinMode(M3_IN2, OUTPUT);
  pinMode(M3_IN3, OUTPUT); pinMode(M3_IN4, OUTPUT);
}

/* ====================================================================== */
/* ======================   STEP A SINGLE MOTOR  ========================= */
/* ====================================================================== */

void stepMotor(int motor, int stepIndex) {

  stepIndex = (stepIndex % 4 + 4) % 4;  // force into range 0–3

  if (motor == 1) {
    digitalWrite(M1_IN1, seq[stepIndex][0]);
    digitalWrite(M1_IN2, seq[stepIndex][1]);
    digitalWrite(M1_IN3, seq[stepIndex][2]);
    digitalWrite(M1_IN4, seq[stepIndex][3]);
  }

  if (motor == 2) {
    digitalWrite(M2_IN1, seq[stepIndex][0]);
    digitalWrite(M2_IN2, seq[stepIndex][1]);
    digitalWrite(M2_IN3, seq[stepIndex][2]);
    digitalWrite(M2_IN4, seq[stepIndex][3]);
  }

  if (motor == 3) {
    digitalWrite(M3_IN1, seq[stepIndex][0]);
    digitalWrite(M3_IN2, seq[stepIndex][1]);
    digitalWrite(M3_IN3, seq[stepIndex][2]);
    digitalWrite(M3_IN4, seq[stepIndex][3]);
  }
}

/* ====================================================================== */
/* ===================   MOVE 3 MOTORS TOGETHER   ======================== */
/* ====================================================================== */

void moveMotors(long s1, int d1, long s2, int d2, long s3, int d3) {

  long maxSteps = max(s1, max(s2, s3));

  for (long i = 0; i < maxSteps; i++) {

    if (i < s1) stepMotor(1, d1 * (i % 4));
    if (i < s2) stepMotor(2, d2 * (i % 4));
    if (i < s3) stepMotor(3, d3 * (i % 4));

    delay(MOTOR_SPEED);
  }
}

/* ====================================================================== */
/* =========================   MAIN LOOP LOGIC   ========================= */
/* ====================================================================== */

void loop() {

  // Convert mm → steps (user distance to steps)
  long steps1 = (long)(abs(X_TARGET_MM) * STEPS_PER_MM);
  long steps2 = (long)(abs(Y_TARGET_MM) * STEPS_PER_MM);
  long steps3 = (long)(abs(Z_TARGET_MM) * STEPS_PER_MM);

  moveMotors(steps1, M1_DIR, steps2, M2_DIR, steps3, M3_DIR);

  if (!CONTINUOUS_MODE)
    while (1);   // Stop forever after one move
}

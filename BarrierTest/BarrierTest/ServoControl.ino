// ---------------------------------------------------------------------------------------------------------------------//
// ------------------------------------------------- VARIABLES ---------------------------------------------------------//
// ---------------------------------------------------------------------------------------------------------------------//

#include <Servo.h>         // Including library of the Servo
Servo ServoArm;            // Creating a servo object
const byte SERVO_PIN = 6;  // The pin the servo-motor gets data from

const int MAX_SERVO_POSITION = 89;  // maximum servo-motor arm position
const int MIN_SERVO_POSITION = 1;   // minimum servo-motor arm position

const byte INCREMENT_SERVO_POSITION = 1;  // increment the servo arm position moves
const int BARRIER_INTERVAL = 50;            // the interval rate of which the servo arm substracts or add the increment

int currentServoPosition;                    // current position of the barrier
unsigned long past_Millis_Barrier = 0;  // past millis of the barrier software timer

boolean is_Barrier_Statements[] = { false, false };  // barrier boolean statements (defined below)
const byte IS_BARRIER_CLOSED = 0;                    // keys to the barrier statements array
const byte IS_BARRIER_OPENED = 1;                    // keys to the barrier statements array


// ---------------------------------------------------------------------------------------------------------------------//
// --------------------------------------------------- SETUP -----------------------------------------------------------//
// ---------------------------------------------------------------------------------------------------------------------//

/* Sets the data pin of the Servo. Sets the servo to maximum position. */
void servoControlSetup() {
  ServoArm.attach(SERVO_PIN);
}


// ---------------------------------------------------------------------------------------------------------------------//
// ------------------------------------------------- FUNCTIONS ---------------------------------------------------------//
// ---------------------------------------------------------------------------------------------------------------------//

/* Add an increment to the servo position */
void addIncrementToServoPosition() {
    currentServoPosition += INCREMENT_SERVO_POSITION;
    Servo.write(currentServoPosition);
}

/* Checks whether max position of servo is reached. Enforces limitations of the servo to protect the hardware. */
boolean maxPositionReached() {
  return currentServoPosition > MAX_SERVO_POSITION;
}

/* Checks whether max position of servo is reached. Enforces limitations of the servo to protect the hardware. */
boolean minPositionReached() {
  return currentServoPosition < MIN_SERVO_POSITION;
}

// ---------------------------------------------------------------------------------------------------------------------//
// --------------------------------------------------- TIMERS ----------------------------------------------------------//
// ---------------------------------------------------------------------------------------------------------------------//

/* Software timer. Returns true if the barrier interval has passed.*/
boolean intervalServoPassed() {
  unsigned long current_Millis = millis();
  if (current_Millis - past_Millis_Barrier > BARRIER_INTERVAL) {
    past_Millis_Barrier = current_Millis;
    return true;
  } else {
    return false;
  }
}

/*  Sets past millis of the barrier to current millis.*/
void resetTimerServo() {
  unsigned long current_Millis = millis();
  past_Millis_Barrier = current_Millis;
}

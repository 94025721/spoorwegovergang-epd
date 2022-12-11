// ---------------------------------------------------------------------------------------------------------------------//
// ------------------------------------------------- VARIABLES ---------------------------------------------------------//
// ---------------------------------------------------------------------------------------------------------------------//


// ---------------------------------------------------------------------------------------------------------------------//
// --------------------------------------------------- SETUP -----------------------------------------------------------//
// ---------------------------------------------------------------------------------------------------------------------//

void ServoLogicSetup() {
  servoControlSetup();
}

// ---------------------------------------------------------------------------------------------------------------------//
// ------------------------------------------------- FUNCTIONS ---------------------------------------------------------//
// ---------------------------------------------------------------------------------------------------------------------//

/* Closing the barrier by an increment. Sets the barrier position to minimum barrier position if barrier is smaller or equal to this value and sets is barrier closed to true.*/
void closing_Barrier() {
  if (barrierPosition <= MIN_SERVO_POSITION) {
    barrierPosition = MIN_SERVO_POSITION;
    is_Barrier_Statements[IS_BARRIER_CLOSED] = true;
  } else if (intervalServoPassed() && !is_Barrier_Statements[IS_BARRIER_CLOSED]) {
    barrierPosition -= BARRIER_MOVEMENT_INCREMENT;
    setServo(barrierPosition);
  }
}

/* Opening the barrier by an increment. Sets the barrier position to maximum barrier position if the barrier is bigger or equal to this value and sets 'is barrier closed' value to true. */
void opening_Barrier() {
  if (barrierPosition >= MAX_SERVO_POSITION) {
    barrierPosition = MAX_SERVO_POSITION;
    is_Barrier_Statements[IS_BARRIER_OPENED] = true;

  } else if (intervalServoPassed()) {
    barrierPosition += BARRIER_MOVEMENT_INCREMENT;
    setServo(barrierPosition);
  }
}

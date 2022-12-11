//_VARIABLES_____________________________________________________________________________________________________________

#include    <Servo.h>                                        // Including library of the Servo
Servo       ServoArm;                                        // Creating a servo object
const byte  SERVO_PIN = 6;                                   // The pin the servo-motor gets data from

const int   MAX_BARRIER_POSITION         = 89;               // maximum servo-motor arm position
const byte  MIN_BARRIER_POSITION         = 1 ;               // minimum servo-motor arm position
const byte  BARRIER_MOVEMENT_INCREMENT   = 1 ;               // increment the servo arm position moves
const int   BARRIER_INTERVAL             = 50;               // the interval rate of which the servo arm substracts or add the increment

int           barrier_Position;                              // current position of the barrier
unsigned long past_Millis_Barrier        = 0;                // past millis of the barrier software timer

boolean       is_Barrier_Statements[]    = { false, false }; // barrier boolean statements (defined below)
const byte    IS_BARRIER_CLOSED          = 0;                // keys to the barrier statements array
const byte    IS_BARRIER_OPENED          = 1;

//_Setup__________________________________________________________________________________________________________________

void servo_Hardware_Setup() {
  /* Sets the data pin of the Servo. Sets the servo to maximum position. 
  */
  ServoArm.attach(SERVO_PIN);
  barrier_Position = MAX_BARRIER_POSITION;
  set_Servo(barrier_Position);
}


//_FUNCTIONS______________________________________________________________________________________________________________


void set_Servo(int servo_Position) {
  /* Sets the servo arm in position.
  */
  ServoArm.write(servo_Position);
}

void reset_Timer_Barrier() {
  /*  Sets past millis of the barrier to current millis.
   */
  unsigned long current_Millis = millis();
  past_Millis_Barrier = current_Millis;
}


void closing_Barrier() {
  /* Closing the barrier by an increment. Sets the barrier position to minimum barrier position if barrier is smaller or equal to this value and sets is barrier closed to true.
  */
  if (barrier_Position <= MIN_BARRIER_POSITION)
  {
    barrier_Position                          = MIN_BARRIER_POSITION;
    is_Barrier_Statements[IS_BARRIER_CLOSED]  = true;
  }
  else if (did_Barrier_Interval_Pass() && !is_Barrier_Statements[IS_BARRIER_CLOSED])
  {
    barrier_Position -= BARRIER_MOVEMENT_INCREMENT;
    set_Servo(barrier_Position);
  }
}

void opening_Barrier() {
  /* Opening the barrier by an increment. Sets the barrier position to maximum barrier position if the barrier is bigger or equal to this value and sets 'is barrier closed' value to true.
  */
  if (barrier_Position >= MAX_BARRIER_POSITION) {
    barrier_Position                          = MAX_BARRIER_POSITION;
    is_Barrier_Statements[IS_BARRIER_OPENED]  = true;

  }
  else if (did_Barrier_Interval_Pass()) {
    barrier_Position += BARRIER_MOVEMENT_INCREMENT;
    set_Servo(barrier_Position);
  }
}

//_TIMERS________________________________________________________________________________________________________

boolean did_Barrier_Interval_Pass() {
  /* Software timer. Returns true if the barrier interval has passed.
  */
  unsigned long current_Millis = millis();
  if (current_Millis - past_Millis_Barrier > BARRIER_INTERVAL) {
    past_Millis_Barrier = current_Millis;
    return true;
  } else {
    return false;
  }
}

//_GETTERS_AND_SETTERS____________________________________________________________________________________________

boolean get_Is_Barrier_Closed() {
  return is_Barrier_Statements[IS_BARRIER_CLOSED];
}

boolean get_Is_Barrier_Opened() {
  return is_Barrier_Statements[IS_BARRIER_OPENED];
}

void set_Is_Barrier_Closed(boolean is_Closed) {
  is_Barrier_Statements[IS_BARRIER_CLOSED] = is_Closed;
}

void set_Is_Barrier_Opened(boolean is_Opened) {
  is_Barrier_Statements[IS_BARRIER_OPENED] = is_Opened;
}

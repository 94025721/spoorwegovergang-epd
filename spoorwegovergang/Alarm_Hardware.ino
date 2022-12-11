//_VARIABLES______________________________________________________________________________________________

const byte      BUZZER_PIN          = 9;                     // Configuration for sending signals to the buzzer from pin.
const int       BUZZER_INTERVAL     = 1000;                  // Sets the inteval of the buzzer in milliseconds

const int       ALARM_HZ[]          = { 100, 1000 };         // Hz of alarm patterns (defined below).
const int       ALARM_DURATION[]    = { 500, 30   };         // Duration of alarm patterns (defined below).
const byte      BEEPING             = 0;                     // Keys to buzzer alarm array.
const byte      TICKING             = 1;

unsigned long   past_Millis_Buzzer  = 0;                     // Saves the last recorded milliseconds of the program

//_SETUP__________________________________________________________________________________________________

void alarm_Hardware_Setup() {
  /*  Sets the pin and mode of the buzzer component. Set the BUZZER to noTone to be certain it makes no sound.
  */
  pinMode(BUZZER_PIN, OUTPUT);
  noTone(BUZZER_PIN);
}

//_FUNCTIONS______________________________________________________________________________________________

void buzzer_Make_Sound(byte pattern) {
  /*  Start the buzzer ticking at a certain Hertz (BUZZER_Hz).
  */
  tone(BUZZER_PIN, ALARM_HZ[pattern], ALARM_DURATION[pattern]);
}

void buzzer_Make_No_Sound() {
  /*  Stop the ticking of the buzzer.
  */
  noTone(BUZZER_PIN);
}

void beeping_Alarm() {
  /* Let the buzzer start and stop making a sound at an interval. The length of the buzz is determined by the return value (boolean)
     of the has_Buzzer_Timer_Passed() function.
  */
  if (did_Interval_Pass_Buzzer()) {
    buzzer_Make_Sound(BEEPING);
  } else {
    return;
  }
}

void ticking_Alarm() {
  /* Let the buzzer start and stop making a sound at an interval. The length of the buzz is determined by the return value (boolean)
     of the has_Buzzer_Timer_Passed() function.
  */
  if (did_Interval_Pass_Buzzer()) {
    buzzer_Make_Sound(TICKING);
  } else {
    return;
  }
}

//_TIMER______________________________________________________________________________________________________

void reset_Alarm_Timer() {
  /*  Resets past millis of the buzzer to current millis.
   */
  unsigned long current_Millis = millis();
  past_Millis_Buzzer = current_Millis;
}

boolean did_Interval_Pass_Buzzer() {
  /*  Software timer for the buzzer
   */
  unsigned long current_Millis = millis();
  if (current_Millis - past_Millis_Buzzer >= BUZZER_INTERVAL) {
    past_Millis_Buzzer = current_Millis;
    return true;
  } else {
    return false;
  }
}

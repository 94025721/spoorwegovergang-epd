//_VARIABLES__________________________________________________________________________________________________

// Saves the last recorded milliseconds of the program
unsigned long pastMillisAlarm = 0;
// Sets the interval of the buzzer in milliseconds
const int BUZZER_INTERVAL = 1000;

//_SETUP__________________________________________________________________________________________________
void AlarmSetup() {
  	alarmControlSetup();
}

//_FUNCTIONS______________________________________________________________________________________________________

/* Let the buzzer start and stop making a sound at an interval. The length of the buzz is determined by the return value (boolean) of the has_Buzzer_Timer_Passed() function.*/
void alarmBeep() {
  if (didIntervalPassAlarm()) {
    lowLongTone();
  }
}

/* Let the buzzer start and stop making a sound at an interval. The length of the buzz is determined by the return value (boolean) of the has_Buzzer_Timer_Passed() function. */
void alarmTick() {
  if (didIntervalPassAlarm()) {
    highShortTone();
  }
}

//_TIMER______________________________________________________________________________________________________

/*  Resets past millis of the buzzer to current millis. */
void resetAlarmTimer() {
  unsigned long currentMillis = millis();
  pastMillisAlarm = currentMillis;
}

/*  Software timer for the buzzer*/
boolean didIntervalPassAlarm() {
  unsigned long currentMillis = millis();
  if (currentMillis - pastMillisAlarm >= BUZZER_INTERVAL) {
    pastMillisAlarm = currentMillis;
    return true;
  } else {
    return false;
  }
}

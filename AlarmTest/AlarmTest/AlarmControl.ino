
//_VARIABLES______________________________________________________________________________________________
const byte BUZZER_PIN = 9;  // Configuration for sending signals to the buzzer from pin.

const byte LOW_TONE = 0;                   // Key to buzzer alarm array.
const byte HIGH_TONE = 1;                  // Key to buzzer alarm array.
const int ALARM_HZ[] = { 100, 1000 };      // Hz of alarm patterns (defined above).
const int ALARM_DURATION[] = { 500, 30 };  // Duration of alarm patterns (defined below).


//_SETUP__________________________________________________________________________________________________

/*  Sets the pin and mode of the buzzer component. Set the BUZZER to noTone to be certain it makes no sound.*/
void alarmControlSetup() {
  pinMode(BUZZER_PIN, OUTPUT);
  noTone(BUZZER_PIN);
}

//_FUNCTIONS______________________________________________________________________________________________

/*  Start the buzzer ticking at a certain Hertz (BUZZER_Hz).*/
void buzzerOn(byte pattern) {
  tone(BUZZER_PIN, ALARM_HZ[pattern], ALARM_DURATION[pattern]);
}

/* Stop the ticking of the buzzer.*/
void buzzerOff() {
  noTone(BUZZER_PIN);
}

/* Make the alarm beep */
void highShortTone() {
  buzzerOn(HIGH_TONE);
}

/* Make the alarm tick */
void lowLongTone() {
  buzzerOn(LOW_TONE);
}
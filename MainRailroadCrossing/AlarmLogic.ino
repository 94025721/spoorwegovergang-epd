//_VARIABLES__________________________________________________________________________________________________

const byte ALARM_OFF       = 0;
const byte ALARM_TICKING   = 1;
const byte ALARM_BEEPING   = 2;

byte alarm_State;

//_SETUP______________________________________________________________________________________________________

void alarm_State_Machine_Setup() {
  /* Sets the alarm state to alarm off. Prepares alarm off by calling entry function.
  */
  alarm_State = ALARM_OFF;
  alarm_Off_Entry();
}

//_STATE_MACHINE______________________________________________________________________________________________

void alarm_State_Machine() {
  switch (alarm_State) {

    //________________________________________________________________________________________________________
    case ALARM_OFF:

      alarm_Off_Do();

      if (get_Did_Countdown_Start()) {
        alarm_Off_Exit();
        alarm_State = ALARM_TICKING;
        alarm_Ticking_Entry();
      }

      if (get_Is_Barrier_Moving()) {
        alarm_Off_Exit();
        alarm_State = ALARM_BEEPING;
        alarm_Beeping_Entry();
      }
      break;

    //________________________________________________________________________________________________________
    case ALARM_TICKING:

      alarm_Ticking_Do();

      if (get_Did_Countdown_End()) {
        alarm_Ticking_Exit();
        alarm_State = ALARM_OFF;
        alarm_Off_Entry();
      }
      break;

    //________________________________________________________________________________________________________
    case ALARM_BEEPING:

      alarm_Beeping_Do();

      if (!get_Is_Barrier_Moving()) {
        alarm_Beeping_Exit();
        alarm_State = ALARM_OFF;
        alarm_Off_Entry();
      }
      break;
  }
}
//_ALARM_OFF_________________________________________________________________________________________________

void alarm_Off_Entry() {}
void alarm_Off_Do   () {}
void alarm_Off_Exit () {}


//_ALARM_TICKING_____________________________________________________________________________________________

void alarm_Ticking_Entry()  {
  reset_Alarm_Timer();
}
void alarm_Ticking_Do() {
  ticking_Alarm();
}
void alarm_Ticking_Exit() {}

//_ALARM_BEEPING______________________________________________________________________________________________

void alarm_Beeping_Entry() {
  reset_Alarm_Timer();
}
void alarm_Beeping_Do() {
  beeping_Alarm();
}
void alarm_Beeping_Exit() {
}

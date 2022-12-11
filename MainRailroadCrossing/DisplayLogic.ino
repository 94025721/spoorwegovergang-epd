//_GLOBAL_VARIABLES_________________________________________________________________________________________________

const unsigned int NUMBERS_DISPLAY[] =
{
  0B0000000000100100, // Nothing
  0B0101111100100100, // 0
  0B0000010100100100, // 1
  0B0011101100100100, // 2
  0B0010111100100100, // 3
  0B0110010100100100, // 4
  0B0110111000100100  // 5
};

const byte      NUMBERS_DISPLAY_LENGTH    = 7;
const byte      DISPLAY_NOTHING           = 0;
const int       INTERVAL_COUNTDOWN        = 1000;

const byte      DISPLAY_OFF               = 0;
const byte      DISPLAY_COUNTDOWN         = 1;

boolean         countdown_Statement[]     = { false, false };
const byte      DID_COUNTDOWN_END         = 0;
const byte      DID_COUNTDOWN_START       = 1;


unsigned long   past_Millis_Countdown;
byte            display_State;
byte            countdown_Count;



//_SETUP____________________________________________________________________________________________________________

void display_State_Machine_Setup() {
  display_State       = DISPLAY_OFF;
  countdown_Count     = NUMBERS_DISPLAY_LENGTH;
  display_Off_Entry();
}


//_STATE_MACHINE____________________________________________________________________________________________________

void display_State_Machine() {
  switch (display_State)
  {
    case DISPLAY_OFF:

      display_Off_Do();

      if (get_Did_Barrier_Just_Opened())
      {
        display_Off_Exit();
        display_State = DISPLAY_COUNTDOWN;
        display_Countdown_Entry();
      }

      break;

    case DISPLAY_COUNTDOWN:

      display_Countdown_Do();

      if (get_Did_Countdown_End())
      {
        display_Countdown_Exit();
        display_State = DISPLAY_OFF;
        display_Off_Entry();
      }
      break;
  }
}


//_DISPLAY_OFF______________________________________________________________________________________________________

void display_Off_Entry() {
  turn_Off_Display();
  set_Did_Barrier_Just_Opened(false);
}

void display_Off_Do() {
  set_Did_Countdown_End(false); // TO-DO: this should be in display_Off_Entry but the boolean will be set to false before the other tabs can use it in their statemachines
}
void display_Off_Exit() {}


//_DISPLAY_COUNTING_________________________________________________________________________________________________

void display_Countdown_Entry() {
  reset_Countdown_Millis();
  reset_Countdown_Count();
  
  set_Did_Countdown_Start(true);
}
void display_Countdown_Do() {
  start_Countdown();
}

void display_Countdown_Exit() {
  set_Did_Countdown_Start(false);
  set_Did_Countdown_End(true);
}


//_FUNCTIONS_______________________________________________________________________________________________________

void turn_Off_Display() {
  /* Sets the shift register to not showing anything.
  */
  set_Current_Pattern(NUMBERS_DISPLAY[DISPLAY_NOTHING]);
}

void start_Countdown() {
  /* Starts the countdown from 6 to 0. Manipulates the current pattern in Shift Register so only the part of the byte responsible for the display changes.
     Does this every interval by timer. One will be retracted from the count every interval.
     If the countdown count is 0 or less, the countdown will be set to 0 AND the boolean variable did_Countdown_End will be set to true.
  */
  if (did_Interval_Pass_Countdown()) {
    set_Current_Display_Pattern_Bitwise(NUMBERS_DISPLAY[countdown_Count]);
    if (countdown_Count <= 0) {
      countdown_Count = 0;
      set_Did_Countdown_End(true);
    } else {
      countdown_Count--;
    }
  }
}


//_SOFTWARE_TIMERS____________________________________________________________________________________________________

boolean did_Interval_Pass_Countdown() {
  /* Software timer for the countdown. Simply returns true if interval has passed.
  */
  unsigned long current_Millis  = millis();

  if (current_Millis - past_Millis_Countdown >= INTERVAL_COUNTDOWN)
  {
    past_Millis_Countdown       = current_Millis;
    return true;
  } 
  else 
  {
    return false;
  }
}

void reset_Countdown_Millis() {
  /*  Sets the past millis of the countdown to current millis. 
   */
  unsigned long current_Millis           = millis();
  past_Millis_Countdown                  = current_Millis;
}

void reset_Countdown_Count() {
  /*  Sets countdown count to the length of the numbers display array (minus one because the count calls the values in the array)
   */
  countdown_Count                        = NUMBERS_DISPLAY_LENGTH - 1;
}


//_GETTERS_SETTERS____________________________________________________________________________________________________

boolean get_Did_Countdown_Start() {
  return countdown_Statement[DID_COUNTDOWN_START];
}

boolean get_Did_Countdown_End() {
  return countdown_Statement[DID_COUNTDOWN_END];
}

void set_Did_Countdown_Start(boolean did_Start) {
  countdown_Statement[DID_COUNTDOWN_START] = did_Start;
}

void set_Did_Countdown_End(boolean did_End) {
  countdown_Statement[DID_COUNTDOWN_END] = did_End;
}

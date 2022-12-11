
//_BUTTON_VARIABLES________________________________________________________________________________________

unsigned long past_Millis_Button  []      = { 0,     0,     0,     0,     0     };   // Array that holds past millis of the buttons (check below for keys)
boolean is_Button_Active          []      = { false, false, false, false, false };   // Array that holds wether a button is active  (check below for keys)

const byte BUTTON_ROAD_NORTH              = 0;                              // Keys to buttons
const byte BUTTON_ROAD_SOUTH              = 1;
const byte BUTTON_TRAIN_EAST              = 2;
const byte BUTTON_TRAIN_WEST              = 3;
const byte BUTTON_COUNT                   = 4;                              // The count of buttons

const byte BUTTON_PEDESTRIAN              = 4;                              // Pedestrian key for past millis and is_Active
const int  PEDESTRIAN_INTERVAL            = 500;                            // In milliseconds

const byte BUTTON_RELEASED_STATE          = 1;                              // Keys for button states
const byte BUTTON_CHECK_PRESSED_STATE     = 2;
const byte BUTTON_PRESSED_STATE           = 3;
const byte BUTTON_CHECK_RELEASED_STATE    = 4;
const byte BUTTON_INTERVAL                = 10;                             // In milliseconds

byte button_State[4];                                                       // Current state




//_SETUP________________________________________________________________________________________

void button_State_Machine_Setup() {
  /* Starting state of the button state machine.
  */
  for (byte button = 0; button < BUTTON_COUNT; button++) {
    button_State[button] = BUTTON_RELEASED_STATE;
    button_Released_Entry(button);
  }
}


//_STATE_MACHINE________________________________________________________________________________

void button_State_Machine_All_Buttons() {
  /*  Enables all the buttons with the same statemachine
  */
  for (byte button = 0; button < BUTTON_COUNT; button++) {
    button_State_Machine(button);
  }
}

void button_State_Machine(byte button) {
  switch (button_State[button]) {

    //________________________________________________________________________________________

    case BUTTON_RELEASED_STATE:

      button_Released_Do(button);

      if (button_Hardware_Down(button))
      {
        button_Released_Exit(button);
        button_State[button] = BUTTON_CHECK_PRESSED_STATE;
        button_Check_Pressed_Entry(button);
      }
      break;

    //________________________________________________________________________________________

    case BUTTON_CHECK_PRESSED_STATE:

      button_Check_Pressed_Do(button);

      if (button_Hardware_Up(button))
      {
        button_Check_Pressed_Exit(button);
        button_State[button] = BUTTON_RELEASED_STATE;
        button_Released_Entry(button);
      }

      else if (button_Hardware_Down(button) && did_Interval_Pass_Button(button))
      {
        button_Check_Pressed_Exit(button);
        button_State[button] = BUTTON_PRESSED_STATE;
        button_Pressed_Entry(button);
      }
      break;

    //________________________________________________________________________________________

    case BUTTON_PRESSED_STATE:

      button_Pressed_Do(button);

      if (button_Hardware_Up(button))
      {
        button_Pressed_Exit(button);
        button_State[button] = BUTTON_CHECK_RELEASED_STATE;
        button_Check_Released_Entry(button);
      }
      break;

    //________________________________________________________________________________________

    case BUTTON_CHECK_RELEASED_STATE:

      button_Check_Released_Do(button);

      if (button_Hardware_Down(button))
      {
        button_Check_Released_Exit(button);
        button_State[button] = BUTTON_PRESSED_STATE;
        button_Pressed_Entry(button);
      }

      else if (button_Hardware_Up(button) && did_Interval_Pass_Button(button))
      {
        button_Check_Released_Exit(button);
        button_State[button] = BUTTON_RELEASED_STATE;
        button_Released_Entry(button);
      }
      break;

  }
}


//_BUTTON_RELEASED_STATE_______________________________________________________________________________________

void button_Released_Entry(byte button) {}
void button_Released_Do(byte button) {}
void button_Released_Exit(byte button) {}


//_BUTTON_CHECK_PRESSED_STATE_______________________________________________________________________________________

void button_Check_Pressed_Entry(byte button) {
  reset_Button_Timer(button);
}

void button_Check_Pressed_Do(byte button) {}
void button_Check_Pressed_Exit(byte button) {}


//_BUTTON_BUTTON_PRESSED_STATE_______________________________________________________________________________________

void button_Pressed_Entry(byte button) {
  set_Button_Active(button);
  check_For_Pedestrian();
}

void button_Pressed_Do(byte button) {}

void button_Pressed_Exit(byte button) {
  reset_Pedestrian_Timer();
}


//_BUTTON_CHECK_RELEASED_STATE_______________________________________________________________________________________

void button_Check_Released_Entry(byte button) {
  reset_Button_Timer(button);
}

void button_Check_Released_Do(byte button) {}
void button_Check_Released_Exit(byte button) {}


//_FUNCTIONS_________________________________________________________________________________________________________

void reset_Button_Timer(byte button) {
  /*  sets the past millis of the button given to the current millis
      @Param button: the targetted button
  */
  unsigned long current_Millis = millis();
  past_Millis_Button[button] = current_Millis;
}

boolean did_Interval_Pass_Button(byte past_Millis) {
  /* Software Timer that returns true if interval variable has passed and false if it didn't pass.
    @param interval:     the interval the timer has to return true
    @param past_Millis:  past millis of the last time the timer returned true (=zero the first time)
  */
  unsigned long current_Millis = millis();
  if (current_Millis - past_Millis_Button[past_Millis] >= BUTTON_INTERVAL) {
    past_Millis_Button[past_Millis] = current_Millis;
    return true;
  } else {
    return false;
  }
}

void check_For_Pedestrian() {
  /*  checks if the road buttons has been activated within the time of the pedestrian timer.
  */
  if ((is_Button_Active[BUTTON_ROAD_SOUTH] | is_Button_Active[BUTTON_ROAD_NORTH]) && !timer_Pedestrian())
  {
    is_Button_Active[BUTTON_PEDESTRIAN]  = true;
  }
}

boolean timer_Pedestrian() {
  /*  timer for the pedestrian feature
  */
  unsigned long current_Millis = millis();
  if (current_Millis - past_Millis_Button[BUTTON_PEDESTRIAN] >= PEDESTRIAN_INTERVAL) {
    return true;
  } else {
    return false;
  }
}

void reset_Pedestrian_Timer() {
  /*  Resets pedestrian timer.
  */
  unsigned long current_Millis            = millis();
  past_Millis_Button[BUTTON_PEDESTRIAN]   = current_Millis;
}

//_GETTERS_&_SETTERS_________________________________________________________________________________________________

void set_Is_Pedestrian_Deactive() {
  is_Button_Active[BUTTON_PEDESTRIAN] = false;
}

void set_Button_Active(byte button) {
  is_Button_Active[button] = true;
}

void set_Train_Button_Deactive() {
  is_Button_Active[BUTTON_TRAIN_EAST] = false;
  is_Button_Active[BUTTON_TRAIN_WEST] = false;
}

void set_Road_Button_North_Deactive() {
  is_Button_Active[BUTTON_ROAD_NORTH] = false;
}

void set_Road_Button_South_Deactive() {
  is_Button_Active[BUTTON_ROAD_SOUTH] = false;
}

boolean get_Is_Pedestrian() {
  return is_Button_Active[BUTTON_PEDESTRIAN];
}

boolean get_Is_Train_Button_Pressed() {
  return is_Button_Active[BUTTON_TRAIN_EAST] || is_Button_Active[BUTTON_TRAIN_WEST];
}

boolean get_Is_Road_Button_North_Pressed() {
  return is_Button_Active[BUTTON_ROAD_NORTH];
}

boolean get_Is_Road_Button_South_Pressed() {
  return is_Button_Active[BUTTON_ROAD_SOUTH];
}

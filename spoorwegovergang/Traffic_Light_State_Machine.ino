//_TRAFFIC_LIGHTS_VARIABLES___________________________________________________________________________________________

const unsigned int TRAFFIC_LIGHTS[] =                                                // Array of all traffic light patterns
{
  0B0000000000100100, // 0: north & south  | red
  0B0000000000010100, // 1: south          | yellow
  0B0000000000001100, // 2: south          | green
  0B0000000000100010, // 3: north          | yellow
  0B0000000000100001, // 4: north          | green
  0B0000000000110110  // 5: north & south  | red
};

const byte      RED_LIGHT                  = 0;                                       // Keys of all traffic light patterns for the array of traffic light patterns and names
const byte      YELLOW_LIGHT_SOUTH         = 1;
const byte      GREEN_LIGHT_SOUTH          = 2;
const byte      YELLOW_LIGHT_NORTH         = 3;
const byte      GREEN_LIGHT_NORTH          = 4;
const byte      RED_YELLOW_LIGHT           = 5;
const byte      TRAFFIC_LIGHTS_COUNT       = 6;


//_TIMER_VARIABLES___________________________________________________________________________________________

const int       INTERVALS_TRAFFIC       [] = {3000,  1500,  2000,  1000,  4000, 5000 };     // Array of all intervals (defined below)
unsigned long   past_Millis_Traffic     [] = {0,     0,     0,     0,     0,    0    };     // Array of all past millis (defined below)
boolean         has_Time_Passed_Traffic [] = {false, false, false, false, false      };     // Array of all statements whether time has passed (defined below)

const byte      GREEN_LIGHT                = 0;                                        // Keys of all timers
const byte      YELLOW_LIGHT               = 1;
const byte      CLEARING_TIME              = 2;
const byte      WARNING_LIGHT              = 3;
const byte      TRAIN_SPEED                = 4;
const byte      PEDESTRIAN_LIGHT           = 5;


//_BOOLEAN_VARIABLES___________________________________________________________________________________________

boolean         traffic_Statements      [] = {false, false, false};
const byte      FLAG_TIMER                 = 0;                                        // Flag boolean for the "did_Flag_Interval_Pass_Traffic()" function (see function description for use)
const byte      IS_WARNING_LIGHT_ON        = 1;
const byte      IS_WARNING_LIGHT_SET       = 2;


//_STATE_MACHINE_VARIABLES______________________________________________________________________________________

const byte      RED_LIGHT_STATE            = 0;                                        // Keys of all traffic light states
const byte      GREEN_LIGHT_NORTH_STATE    = 1;
const byte      YELLOW_LIGHT_NORTH_STATE   = 2;
const byte      GREEN_LIGHT_SOUTH_STATE    = 3;
const byte      YELLOW_LIGHT_SOUTH_STATE   = 4;
const byte      WARNING_LIGHT_STATE        = 5;

byte            traffic_Light_State;                                                   // Current traffic light state used in the "traffic_Light_State_Machine()"


//_SETUP_________________________________________________________________________________________________________

void traffic_Light_State_Machine_Setup() {
  /* Sets the starting point for the raffic light
  */
  traffic_Light_State = RED_LIGHT_STATE;
  red_Light_State_Entry();
}


//_STATE_MACHINE_________________________________________________________________________________________________

void traffic_Light_State_Machine() {
  switch (traffic_Light_State) {

    //___________________________________________________________________________________________________________

    case RED_LIGHT_STATE:

      red_Light_State_Do();

      if (did_Interval_Pass_Traffic(CLEARING_TIME)     // True if clearing time has passed & road button SOUTH has been pressed
          && get_Is_Road_Button_South_Pressed()
          && !get_Is_Train_Button_Pressed())
      {
        red_Light_State_Exit();
        traffic_Light_State = GREEN_LIGHT_SOUTH_STATE;
        green_Light_South_State_Entry();
      }

      else if (did_Interval_Pass_Traffic(CLEARING_TIME)    // True if clearing time has passed & road button NORTH has been pressed
               && get_Is_Road_Button_North_Pressed()
               && !get_Is_Train_Button_Pressed())
      {
        red_Light_State_Exit();
        traffic_Light_State = GREEN_LIGHT_NORTH_STATE;
        green_Light_North_State_Entry();

      }

      else if (get_Is_Train_Button_Pressed() && did_Interval_Pass_Traffic(CLEARING_TIME))  // True if train button has been pressed
      {
        red_Light_State_Exit();
        traffic_Light_State = WARNING_LIGHT_STATE;
        warning_Light_State_Entry();
      }

      break;

    //___________________________________________________________________________________________________________

    case GREEN_LIGHT_NORTH_STATE:

      green_Light_North_State_Do();

      if ((did_Interval_Pass_Traffic(GREEN_LIGHT) && did_Interval_Pedestrian_Pass())     // True if green waiting time has passed AND if pedestrian interval passed
          || (get_Is_Train_Button_Pressed() && did_Interval_Pass_Train_Speed()))         // OR if train button is pressed && train speed interval has passed
      {
        green_Light_North_State_Exit();
        traffic_Light_State = YELLOW_LIGHT_NORTH_STATE;
        yellow_Light_North_State_Entry();
      }

      break;

    //___________________________________________________________________________________________________________

    case YELLOW_LIGHT_NORTH_STATE:

      yellow_Light_North_State_Do();

      if (did_Interval_Pass_Traffic(YELLOW_LIGHT))  // True if yellow waiting time has passed
      {
        yellow_Light_North_State_Exit();
        traffic_Light_State = RED_LIGHT_STATE;
        red_Light_State_Entry();
      }
      break;

    //___________________________________________________________________________________________________________

    case GREEN_LIGHT_SOUTH_STATE:

      green_Light_South_State_Do();

      if ((did_Interval_Pass_Traffic(GREEN_LIGHT) && did_Interval_Pedestrian_Pass())  // True if green waiting time has passed AND if pedestrian interval passed
          || (get_Is_Train_Button_Pressed() && did_Interval_Pass_Train_Speed()))      // OR if train button is pressed && train speed interval has passed
      {
        green_Light_South_State_Exit();
        traffic_Light_State = YELLOW_LIGHT_SOUTH_STATE;
        yellow_Light_South_State_Entry();
      }
      break;

    //___________________________________________________________________________________________________________

    case YELLOW_LIGHT_SOUTH_STATE:

      yellow_Light_South_State_Do();

      if (did_Interval_Pass_Traffic(YELLOW_LIGHT))      // True if yellow waiting time has passed
      {
        yellow_Light_South_State_Exit();
        traffic_Light_State = RED_LIGHT_STATE;
        red_Light_State_Entry();
      }
      break;

    //___________________________________________________________________________________________________________

    case WARNING_LIGHT_STATE:

      warning_Light_State_Do();

      if (get_Did_Countdown_End()) {
        warning_Light_State_Exit();
        traffic_Light_State = RED_LIGHT_STATE;
        red_Light_State_Entry();
      }
      break;
  }
}


//_RED_LIGHT_STATE______________________________________________________________________________________________________________

void red_Light_State_Entry() {
  reset_Timer(CLEARING_TIME);
  set_Traffic_Light(RED_LIGHT);
}

void red_Light_State_Do() {

}

void red_Light_State_Exit() {

}


//_GREEN_LIGHT_NORTH_STATE______________________________________________________________________________________________________

void green_Light_North_State_Entry() {
  reset_Timer(GREEN_LIGHT);
  reset_Timer(TRAIN_SPEED);
  set_Traffic_Light(GREEN_LIGHT_NORTH);

  reset_Pedestrian_Traffic_Timer();
}

void green_Light_North_State_Do() {
}

void green_Light_North_State_Exit() {
  set_Is_Pedestrian_Deactive();
}


//_YELLOW_LIGHT_NORTH_STATE_____________________________________________________________________________________________________

void yellow_Light_North_State_Entry() {
  reset_Timer(YELLOW_LIGHT);
  set_Traffic_Light(YELLOW_LIGHT_NORTH);
}

void yellow_Light_North_State_Do() {
}

void yellow_Light_North_State_Exit() {
  set_Road_Button_North_Deactive();
}


//_GREEN_LIGHT_SOUTH_STATE______________________________________________________________________________________________________

void green_Light_South_State_Entry() {
  reset_Timer(TRAIN_SPEED);
  reset_Timer(GREEN_LIGHT);
  set_Traffic_Light(GREEN_LIGHT_SOUTH);

  reset_Pedestrian_Traffic_Timer();
}

void green_Light_South_State_Do() {
}

void green_Light_South_State_Exit() {
  set_Is_Pedestrian_Deactive();
}


//_YELLOW_LIGHT_SOUTH_STATE_____________________________________________________________________________________________________

void yellow_Light_South_State_Entry() {
  reset_Timer(YELLOW_LIGHT);
  set_Traffic_Light(YELLOW_LIGHT_SOUTH);
}

void yellow_Light_South_State_Do() {}

void yellow_Light_South_State_Exit() {
  set_Road_Button_South_Deactive();
}


//_WARNING_LIGHT_STATE__________________________________________________________________________________________________________

void warning_Light_State_Entry() {
  set_Is_Warning_Light_On(true);
}
void warning_Light_State_Do() {
  warning_Light();
}
void warning_Light_State_Exit() {
  set_Is_Warning_Light_On(false);
  reset_Timer(CLEARING_TIME);
}


//_FUNCTIONS____________________________________________________________________________________________________________________

void set_Traffic_Light(byte selected_Light) {
  /* Sets traffic light to given traffic light pattern
  */
  set_Current_Pattern(TRAFFIC_LIGHTS[selected_Light]);
}

void set_Warning_Light(byte selected_Light) {
  /* Sets traffic light to warning lights.
  */
  set_Current_Traffic_Pattern_Bitwise(TRAFFIC_LIGHTS[selected_Light]);
}

void warning_Light() {
  /* Switches the traffic light from both red to both red and yellow in a given interval.
     Uses is_Warning_Light_Set boolean so it sets the shift register once every interval.
  */
  if (did_Flag_Interval_Pass_Traffic(WARNING_LIGHT) && !traffic_Statements[IS_WARNING_LIGHT_SET])
  {
    set_Current_Traffic_Pattern_Bitwise(TRAFFIC_LIGHTS[RED_YELLOW_LIGHT]);
    traffic_Statements[IS_WARNING_LIGHT_SET] = true;
  }
  else if (!did_Flag_Interval_Pass_Traffic(WARNING_LIGHT) && traffic_Statements[IS_WARNING_LIGHT_SET])
  {
    set_Current_Traffic_Pattern_Bitwise(TRAFFIC_LIGHTS[RED_LIGHT]);
    traffic_Statements[IS_WARNING_LIGHT_SET] = false;
  }
}

//_TIMERS________________________________________________________________________________________________________

boolean did_Flag_Interval_Pass_Traffic(byte timer) {
  /* Software timer that returns the boolean value of flag. It will swap variable flag every interval from true to false or vice versa.
     @param timer: this is a target for the timer array.
  */
  unsigned long current_Millis = millis();
  if (current_Millis - past_Millis_Traffic[timer] >= INTERVALS_TRAFFIC[timer])
  {
    past_Millis_Traffic [timer]       =  current_Millis;                      // Set past millis to current millis
    traffic_Statements  [FLAG_TIMER]  = !traffic_Statements[FLAG_TIMER];      // Set the count to zero if it exceeds the array length of the traffic lights array

    return traffic_Statements[FLAG_TIMER];
  }
  else
  {
    return traffic_Statements[FLAG_TIMER];
  }
}


boolean did_Interval_Pass_Traffic(byte timer) {
  /* Software Timer that returns:
      - true if interval variable has passed
      - true if the targeted timer's interval already has passed
      - false if it didn't pass.
     @param timer: this is the position of the selected timer withing the timer arrays.
  */
  unsigned long current_Millis  = millis();               // Save last millis()

  if ((current_Millis - past_Millis_Traffic[timer] >= INTERVALS_TRAFFIC[timer]) || has_Time_Passed_Traffic[timer])
  {
    past_Millis_Traffic[timer]        = current_Millis;   // Set past millis to current millis
    has_Time_Passed_Traffic[timer]    = true;             // Set timer boolean to true so timer interval has passed

    return has_Time_Passed_Traffic[timer];
  }
  else
  {
    return has_Time_Passed_Traffic[timer];
  }
}


boolean did_Interval_Pass_Train_Speed() {
  /*  Reads potentiometer data. Multiplies the readings times the train speed interval. Uses this new interval in the software timer.
  */

  float potmeter_Measure          = get_Potmeter_Reading();
  int interval_Train_Speed        = INTERVALS_TRAFFIC[TRAIN_SPEED] * potmeter_Measure;
  unsigned long current_Millis    = millis();

  if (current_Millis - past_Millis_Traffic[TRAIN_SPEED] >= interval_Train_Speed)
  {
    past_Millis_Traffic[TRAIN_SPEED] = current_Millis;

    return true;
  }
  else
  {
    return false;
  }
}


boolean did_Interval_Pedestrian_Pass() {
  /*  Returns true if pedestrian button is deactive. Else returns true if button is active and interval has passed. Else returns false if neither statements pass.
  */

  unsigned long current_Millis = millis();

  if (!get_Is_Pedestrian())
  {
    return true;
  }
  else if (current_Millis - past_Millis_Traffic[PEDESTRIAN_LIGHT] >= INTERVALS_TRAFFIC[PEDESTRIAN_LIGHT])
  {
    Serial.print("ACTIVE");
    return true;
  }
  else
  {
    return false;
  }
}


void reset_Pedestrian_Traffic_Timer() {
  /*  Resets pedestrian past millis.
   */
  unsigned long current_Millis = millis();
  past_Millis_Traffic[PEDESTRIAN_LIGHT] = current_Millis;
}


void reset_Timer(byte timer) {
  /* Resets the past millis of a timer in the past_Millis_Traffic Array
     @param timer: targeted timer from the past_Millis_Traffic Array
  */
  unsigned long current_Millis    = millis();                 // save last millis()
  past_Millis_Traffic[timer]      = current_Millis;           // set past millis to current millis to reset
  has_Time_Passed_Traffic[timer]  = false;                    // set timer boolean to false to reset
}


//_GETTER_AND_SETTERS__________________________________________________________________________________________

void set_Is_Warning_Light_On(boolean are_On) {
  traffic_Statements[IS_WARNING_LIGHT_ON] = are_On;
}

boolean get_Are_Warning_Lights_On() {
  return traffic_Statements[IS_WARNING_LIGHT_ON];
}

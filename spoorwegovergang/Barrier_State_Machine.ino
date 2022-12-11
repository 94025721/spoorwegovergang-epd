
//_VARIABLES_____________________________________________________________________________________________________________

const byte  BARRIER_OPEN            = 0;                          // Barrier statemachine states
const byte  BARRIER_IS_CLOSING      = 1;
const byte  BARRIER_CLOSED          = 2;
const byte  BARRIER_IS_OPENING      = 3;
byte        barrier_State;

boolean     barrier_Statements[]    = { false, false, false };    // barrier boolean statements (defined below)
const byte  IS_BARRIER_JUST_OPENED  = 0;                          // keys to the barrier statements array
const byte  IS_BARRIER_MOVING       = 1;
const byte  IS_BARRIER_OPEN         = 2;

int         barrier_Opening_Count;                                // keeps the count of how many times the barrier has been opened


//_SETUP__________________________________________________________________________________________________________________

void barrier_Setup() {
  barrier_State           = BARRIER_OPEN;
  barrier_Open_Entry();
}

//_STATE_MACHINE__________________________________________________________________________________________________________

void barrier_State_Machine() {
  
  switch (barrier_State) 
  {
    //____________________________________________________________________________________________________________________
    
    case BARRIER_OPEN:

      barrier_Open_Do();

      if (get_Is_Train_Button_Pressed() && get_Are_Warning_Lights_On())
      {
        barrier_Open_Exit();
        barrier_State = BARRIER_IS_CLOSING;
        barrier_Is_Closing_Entry();
      }

      break;

    //____________________________________________________________________________________________________________________
    
    case BARRIER_IS_CLOSING:

      barrier_Is_Closing_Do();

      if (get_Is_Barrier_Closed())
      {
        barrier_Is_Closing_Exit();
        barrier_State = BARRIER_CLOSED;
        barrier_Closed_Entry();
      }
      break;

    //____________________________________________________________________________________________________________________
    
    case BARRIER_CLOSED:

      barrier_Closed_Do();

      if (get_Is_Train_Button_Pressed()) {
        barrier_Closed_Exit();
        barrier_State = BARRIER_IS_OPENING;
        barrier_Is_Opening_Entry();
      }

      break;

    //____________________________________________________________________________________________________________________
    
    case BARRIER_IS_OPENING:

      barrier_Is_Opening_Do();

      if (get_Is_Barrier_Opened())
      {
        barrier_Is_Opening_Exit();
        barrier_State = BARRIER_OPEN;
        barrier_Open_Entry();
      }

      break;
  }
}

//_BARRIER_OPEN_____________________________________________________________________________________________________________________

void barrier_Open_Entry() {}
void barrier_Open_Do() {}
void barrier_Open_Exit() {}

//_BARRIER_IS_OPENING_____________________________________________________________________________________________________________________

void barrier_Is_Opening_Entry() {
  reset_Timer_Barrier();
  set_Is_Barrier_Moving(true);
}
void barrier_Is_Opening_Do() {
  opening_Barrier();
}
void barrier_Is_Opening_Exit() {
  set_Is_Barrier_Opened(false);
  set_Is_Barrier_Moving(false);
  set_Did_Barrier_Just_Opened(true);
  
  set_Train_Button_Deactive();

  add_Barrier_Opening_Count();
  Serial.print("Barrier total openings: ");
  Serial.println(get_Barrier_Opening_Count());
}

//_BARRIER_CLOSED______________________________________________________________________________________________________________________

void barrier_Closed_Entry() {}
void barrier_Closed_Do() {}
void barrier_Closed_Exit() {}


//_BARRIER_IS_CLOSING_____________________________________________________________________________________________________________________

void barrier_Is_Closing_Entry() {
  reset_Timer_Barrier();
  set_Is_Barrier_Moving(true);
}
void barrier_Is_Closing_Do() {
  closing_Barrier();
}
void barrier_Is_Closing_Exit() {
  set_Is_Barrier_Closed(false);
  set_Is_Barrier_Moving(false);
  set_Train_Button_Deactive();
}


//__FUNCTIONS______________________________________________________________________________________________________________________

void add_Barrier_Opening_Count() {
  /* add one to the barrier count
  */
  barrier_Opening_Count++;
}


//_GETTERS_AND_SETTERS_______________________________________________________________________________________________________________

void set_Did_Barrier_Just_Opened(boolean did_Open) {
  barrier_Statements[IS_BARRIER_JUST_OPENED] = did_Open;
}

void set_Is_Barrier_Moving(boolean is_Moving) {
  barrier_Statements[IS_BARRIER_MOVING] = is_Moving;
}

boolean get_Did_Barrier_Just_Opened() {
  return barrier_Statements[IS_BARRIER_JUST_OPENED];
}

boolean get_Is_Barrier_Moving() {
  return barrier_Statements[IS_BARRIER_MOVING];
}

int get_Barrier_Opening_Count() {
  return barrier_Opening_Count;
}

void reset_Barrier_Opening_Count() {
  barrier_Opening_Count = 0;
}

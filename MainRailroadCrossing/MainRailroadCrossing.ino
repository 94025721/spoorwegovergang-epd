void setup() {
  serial_Setup();
  Serial.begin(9600);
  
  servo_Hardware_Setup();
  barrier_Setup();
  
  button_Hardware_Setup();
  button_State_Machine_Setup();
  
  shift_Register_Setup();
  display_State_Machine_Setup();
  traffic_Light_State_Machine_Setup();
  
  alarm_State_Machine_Setup();
  alarm_Hardware_Setup();
  
}

void loop() {
  display_State_Machine();
  barrier_State_Machine();
  button_State_Machine_All_Buttons();
  traffic_Light_State_Machine();
  alarm_State_Machine();
  serial_Loop();
}

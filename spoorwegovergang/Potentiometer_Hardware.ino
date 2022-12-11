
//_SETUP___________________________________________________________________________________________________

void potmeter_Setup() {
  pinMode(A0, INPUT);
}

//_FUNCTION___________________________________________________________________________________________________

float get_Potmeter_Reading() {
  float read_Data     = analogRead(A0);
  float mapped_Data   = map(read_Data, 0, 1024, 0, 100);
  mapped_Data /= 100;
  return mapped_Data;
}

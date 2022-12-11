void serial_Setup() {
  Serial.begin(9600);
}

char input_Serial() {
  if(Serial.available() > 0) {
    return Serial.read();
  } else {
    return '0';
  }
}

void serial_Loop() {
  if(input_Serial() == 'r') {
    reset_Barrier_Opening_Count();
    Serial.println("Barrier Count Resetted");
  }
}

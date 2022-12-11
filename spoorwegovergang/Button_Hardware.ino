//_VARIABLES___________________________________________________________________________________________________

const byte BUTTON_PINS[]    = {2, 3, 4, 5};      // Configuration for reading the pin connected to the button
const byte BUTTON_PIN_COUNT = 4;                 // The length of the BUTTON_PINS array


//_SETUP___________________________________________________________________________________________________

void button_Hardware_Setup() {
  /* Setting up all the pins of the buttons on INPUT-mode so they can be read. 
  */
  for (int button = 0; button < BUTTON_PIN_COUNT; button++) {
    pinMode(BUTTON_PINS[button], INPUT);
  }
}


//_FUNCTIONS___________________________________________________________________________________________________

boolean button_Hardware_Down(byte button) {
/*  Returns the read data on the pin of the button if HIGH is read.
 *  @param button: one of the buttons on the breadboard 
 */
  return (digitalRead(BUTTON_PINS[button]) == HIGH);
}

boolean button_Hardware_Up(int button) {
/* Returns the flipped read data on the pin of the 'button_Hardware_Down(byte)' function
*/
  return !button_Hardware_Down(button);
}

//_GLOBAL_VARIABLES_________________________________________________________________________________________________

const byte DS                    = 13;                // Data Serial
const byte ST_CP                 = 12;                // Latch Clock
const byte SH_CP                 = 11;                // Clock Pin
const int  SHIFT_REGISTERS_BITS  = 16;                // The sum of bits of the MSR and CSR

unsigned int current_Pattern = 0B0000000000000000;    // Current pattern for the shift register


//_FUNCTIONS________________________________________________________________________________________________________

void shift_Register_Setup() {
  /* Sets the pins of the main shift register to OUTPUT mode so it can send date to the SR
  */
  pinMode(ST_CP, OUTPUT);
  pinMode(SH_CP, OUTPUT);
  pinMode(DS, OUTPUT);
}

void set_Shift_Register(unsigned int pattern)
/*  Sets serially the two shift registers.
    @Param pattern in 16-bits so it has enough to set both 8-bit shift registers.
*/
{
  digitalWrite(ST_CP, LOW);                                         // Latch Clock is set to LOW to be sure

  for (int bitNr = 0; bitNr < SHIFT_REGISTERS_BITS; bitNr++)
  {
    digitalWrite(SH_CP, LOW);                                       // Shift clock is set to LOW

    unsigned int edited_16_Bit = pattern << bitNr;                  // DS is set to the value of the bit
    edited_16_Bit = edited_16_Bit >> (SHIFT_REGISTERS_BITS - 1);

    if (edited_16_Bit == 0) {
      digitalWrite(DS, LOW);
    }
    else if (edited_16_Bit == 1) {
      digitalWrite(DS, HIGH);
    }

    digitalWrite(SH_CP, HIGH);                                       // Shift clock is set to HIGH
  }

  digitalWrite(ST_CP, HIGH);                                         // Latch clock is set to HIGH to copy the 2 byte
  digitalWrite(ST_CP, LOW);                                          // Latch clock is set to LOW to save the next pattern
}


//_GETTERS_&_SETTERS______________________________________________________________________________________________________

void set_Current_Pattern(unsigned int new_Pattern) {
  /* Sets the current_Pattern and the shift register
     @param new_Pattern: the given pattern in 2 byte
  */
  current_Pattern = new_Pattern;
  set_Shift_Register(current_Pattern);
}

void set_Current_Traffic_Pattern_Bitwise(unsigned int new_Pattern) {
  /*  Uses bitshift operator to turn the traffic lights part of the byte to zero. Adds the new traffic pattern to current pattern. Sets the shiftregister.
      @Param new_Pattern: the pattern given by the traffic light
  */
  current_Pattern = current_Pattern >> 8;                             // Set the last 8 bits to zero.
  current_Pattern = current_Pattern << 8;                             // ...
  current_Pattern = current_Pattern | new_Pattern;                    // Adds the parameter value to the current pattern
  set_Shift_Register(current_Pattern);                                // Set shift register to current pattern
}

void set_Current_Display_Pattern_Bitwise(unsigned int new_Pattern) {
  /*  Uses bitshift operator to turn the display part of the byte to zero. Adds the new traffic pattern to current pattern. Sets the shiftregister.
     @Param new_Pattern: the pattern given by the display
  */
  current_Pattern = current_Pattern << 8;                            // Sets the first 8 bits to zero.
  current_Pattern = current_Pattern >> 8;                            // ...
  current_Pattern = current_Pattern | new_Pattern;                   // Adds the parameter value to the current pattern
  set_Shift_Register(current_Pattern);                               // Set shift register to current 
}

//www.elegoo.com
//2016.12.9 
#include <Arduino.h>

int tDelay = 100;
int latchPin = 11;      // (11) ST_CP [RCK] on 74HC595
int clockPin = 9;      // (9) SH_CP [SCK] on 74HC595
int dataPin = 12;     // (12) DS [S1] on 74HC595

byte leds = 0;

// Updates the 74HC595 shift register with the current LED state.
void updateShiftRegister();
void all_left_to_right();
void one_back_and_forth();
void two_inward_outward();
void pulse_wave();

void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}

void loop() 
{
  all_left_to_right(); // Turn on all LEDs one by one from left to right
  one_back_and_forth(); // Turn on LEDs one by one from left to right, then right to left (ironman style)
  two_inward_outward(); // Two LEDs Moving Inward and Outward 
  pulse_wave(); // Pulse Wave / Growing Bar

  //#########################################################
  
  // Clear for next cycle
  leds = 0;
  updateShiftRegister();
  delay(tDelay);
}

// ######### End of the main loop
// #####################################################
// FUNCTIONS

// Updates the 74HC595 shift register with the current LED state.
void updateShiftRegister(){
  Serial.print("Updating shift register... ");
  Serial.println(byte(leds), BIN); // Print the current state of leds in binary format

   static bool latchState = HIGH; // Cache the state of latchPin
   // Ensure latchPin is LOW before shifting out data
   if (latchState != LOW) {
       digitalWrite(latchPin, LOW);
       latchState = LOW;
   }
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   if (latchState != HIGH) {
       digitalWrite(latchPin, HIGH);
       latchState = HIGH;
   }
   digitalWrite(latchPin, HIGH);
}


//Turn on all LEDs one by one from left to right
void all_left_to_right(){

  for (int i = 0; i < 8; i++) 
  {
    bitSet(leds, i);
    updateShiftRegister();
    delay(tDelay);
  }
}

// Turn on LEDs one by one from left to right, then right to left (ironman style)
void one_back_and_forth(){
  for (int i = 0; i < 8; i++) {
  leds = 1 << i;
  updateShiftRegister();
  delay(100);
  }
  
  for (int i = 6; i >= 1; i--) {
    leds = 1 << i;
    updateShiftRegister();
    delay(100);
  }
}


// Two LEDs Moving Inward and Outward
void two_inward_outward(){
  // Moving inward (outer to center)
  for (int i = 0; i < 4; i++) {
    leds = (1 << i) | (1 << (7 - i));
    updateShiftRegister();
    delay(100);
  }
  // Moving outward (center to edges)
  for (int i = 2; i >= 0; i--) {
    leds = (1 << i) | (1 << (7 - i));
    updateShiftRegister();
    delay(100);
  }
}

// Pulse Wave / Growing Bar
void pulse_wave(){

 for (int i = 0; i <= 3; i++) {
    leds |= (1 << (3 - i)); // Center-left
    leds |= (1 << (4 + i)); // Center-right
    updateShiftRegister();
    delay(100);
  }
}
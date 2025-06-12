// Arduino board: This project is designed for the Arduino Uno board.
// Libraries: This code uses the Arduino core library for basic functionality.
#include <Arduino.h>
#include <HCSR04.h>
int tDelay = 100;
int latchPin = 11;      // (11) ST_CP [RCK] on 74HC595
int clockPin = 9;      // (9) SH_CP [SCK] on 74HC595
int dataPin = 12;     // (12) DS [S1] on 74HC595
int echoPin = 7;      // (7) Echo pin for ultrasonic sensor
int trigPin = 8;      // (8) Trigger pin for ultrasonic sensor
long distance{}; // Variable to store the distance measured by the ultrasonic sensor
int mappedValue = 0; // Variable to store the mapped value of the distance
byte leds = 0; // Variable to store the state of the LEDs

UltraSonicDistanceSensor ultrasonicSensor(trigPin, echoPin); 
// Updates the 74HC595 shift register with the current LED state.

//function prototypes
void updateShiftRegister();
void all_left_to_right();
void one_back_and_forth();
void two_inward_outward();
void pulse_wave();
void activate_map_leds(int &ledIndex, byte &leds);
int map(int ditance);

void setup() 
{
  Serial.begin(9600); // Initialize serial communication for debugging
  Serial.println("74HC595 LED Control with Ultrasonic Sensor");
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}

void loop() 
{

  leds = 0;

  // Measure distance using the ultrasonic sensor
  distance = ultrasonicSensor.measureDistanceCm(); // Measure distance in cm
  mappedValue = map(distance); // Map the distance to a value between 0 and 7
  Serial.print("Distance: "); 
  Serial.print(distance); // Print the distance
  Serial.print(" cm, Mapped Value: ");  
  Serial.println(mappedValue); // Print the mapped value
  // Clear for next cycle
  if (mappedValue >= 0)
    activate_map_leds(mappedValue, leds); // Activate the LED corresponding to the mapped value
  else {
    Serial.println("Invalid distance, no LEDs activated.");
  }
  updateShiftRegister(); // Update the shift register with the current LED state
  delay(500);
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

}

// Maps the distance measured by the ultrasonic sensor to a value between 0 and 7
int map(int distance) {
  // Map the distance to a value between 0 and 7
  // Assuming the distance is in cm and we want to map it to 8 LEDs
  if (distance < 0 || distance > 400) {
    return -1; // Invalid distance
  }
  return map(distance, 0, 75, 0, 7);
}

// Activate the LED corresponding to the mapped value
void activate_map_leds(int &mappedValue, byte &leds) {
  for(int i =0; i <= mappedValue; i++) {
    leds |= (1 << i); // Set the bit corresponding to the mapped value
  }
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
  delay(tDelay);
  }
  
  for (int i = 6; i >= 1; i--) {
    leds = 1 << i;
    updateShiftRegister();
    delay(tDelay);
  }
}


// Two LEDs Moving Inward and Outward
void two_inward_outward(){
  // Moving inward (outer to center)
  for (int i = 0; i < 4; i++) {
    leds = (1 << i) | (1 << (7 - i));
    updateShiftRegister();
    delay(tDelay);
  }
  // Moving outward (center to edges)
  for (int i = 2; i >= 0; i--) {
    leds = (1 << i) | (1 << (7 - i));
    updateShiftRegister();
    delay(tDelay);
  }
}

// Pulse Wave / Growing Bar
void pulse_wave(){

 for (int i = 0; i <= 3; i++) {
    leds |= (1 << (3 - i)); // Center-left
    leds |= (1 << (4 + i)); // Center-right
    updateShiftRegister();
    delay(tDelay);
  }
}
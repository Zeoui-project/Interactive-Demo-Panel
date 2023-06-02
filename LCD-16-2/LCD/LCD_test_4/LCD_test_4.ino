#include <Encoder.h>

// Rotary Encoder Pins
#define PIN_ENCODER_A 6
#define PIN_ENCODER_B 9


// Create an Encoder object
Encoder encoder(PIN_ENCODER_A, PIN_ENCODER_B);

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the current position of the encoder
  int currentPosition = encoder.read();

  // Print the current position
  Serial.println(currentPosition);
}
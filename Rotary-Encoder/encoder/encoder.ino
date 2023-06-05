// Rotary Encoder Pins
#define PIN_ENCODER_A 6
#define PIN_ENCODER_B 7

// Variables to store current and previous state of the encoder
volatile int encoderState;
volatile int lastEncoderState;

// Variables to keep track of the position and direction of the encoder
volatile int encoderPosition = 0;
volatile int encoderDirection = 0;

void setup() {
  // Set encoder pins as inputs
  pinMode(PIN_ENCODER_A, INPUT);
  pinMode(PIN_ENCODER_B, INPUT);
  
  // Enable internal pull-up resistors
  digitalWrite(PIN_ENCODER_A, HIGH);
  digitalWrite(PIN_ENCODER_B, HIGH);

  // Attach interrupts to the encoder pins
  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_A), handleEncoderInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_B), handleEncoderInterrupt, CHANGE);

  // Initialize encoder state
  encoderState = digitalRead(PIN_ENCODER_A) << 1 | digitalRead(PIN_ENCODER_B);
  lastEncoderState = encoderState;
}

void loop() {
  // Check if the encoder position has changed
  if (encoderDirection != 0) {
    // Print the new position and direction
    Serial.print("Encoder Position: ");
    Serial.print(encoderPosition);
    Serial.print(", Direction: ");
    Serial.println(encoderDirection);

    // Reset the direction
    encoderDirection = 0;
  }
  
  // Add other code or functionality here
  // ...

  // Delay for stability
  delay(10);
}

void handleEncoderInterrupt() {
  // Read the current state of the encoder pins
  int pinAState = digitalRead(PIN_ENCODER_A);
  int pinBState = digitalRead(PIN_ENCODER_B);

  // Calculate the current state of the encoder
  encoderState = pinAState << 1 | pinBState;

  // Determine the direction of rotation
  switch (encoderState) {
    case 0b00:
    case 0b11:
      if (lastEncoderState == 0b01 || lastEncoderState == 0b10) {
        encoderPosition += encoderDirection;
        encoderDirection = 0;
      }
      break;
    case 0b01:
      if (lastEncoderState == 0b00) {
        encoderDirection = 1;
      } else if (lastEncoderState == 0b11) {
        encoderDirection = -1;
      }
      break;
    case 0b10:
      if (lastEncoderState == 0b11) {
        encoderDirection = 1;
      } else if (lastEncoderState == 0b00) {
        encoderDirection = -1;
      }
      break;
  }

  // Update the last encoder state
  lastEncoderState = encoderState;
}
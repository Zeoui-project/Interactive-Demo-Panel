#include <LiquidCrystal.h>
#define PIN_ENCODER_A 6
#define PIN_ENCODER_B 7

// Variables to store current and previous state of the encoder
volatile int encoderState;
volatile int lastEncoderState;

// Variables to keep track of the position and direction of the encoder
volatile int encoderPosition = 0;
volatile int encoderDirection = 0;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  // Define the LCD object and pin connections

const int progressBarLength = 16;  // Length of the progress bar
const char progressBarChar = '#'; // Character used to represent progress

void setup() {
  lcd.begin(16, 2);  // Initialize the LCD with 16 columns and 2 rows
  lcd.clear();  // Clear the LCD

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
  static int progress = 0;
  static int lastProgress = 0;
  
  // Update the progress based on the encoder movement
  progress += encoderDirection;
  
  // Limit the progress within the range 0-100
  if (progress < 0) {
    progress = 0;
  } else if (progress > 100) {
    progress = 100;
  }
  
  // Calculate the number of progress bar characters to display
  int progressBarFill = (progress * progressBarLength) / 100;

  // Update the progress bar only when there's a change
  if (progress != lastProgress) {
    // Print the progress bar on the LCD
    lcd.setCursor(0, 1);
    for (int i = 0; i < progressBarLength; i++) {
      if (i < progressBarFill) {
        lcd.print(progressBarChar);
      } else {
        lcd.print(" ");
      }
    }

    lastProgress = progress;
  }

  // Delay to avoid rapid updates
  delay(100);
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
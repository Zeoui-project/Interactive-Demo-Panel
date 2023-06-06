#include <LiquidCrystal.h>
#include <Encoder.h>

// LCD configuration
const int LCD_RS = 12;
const int LCD_EN = 11;
const int LCD_D4 = 5;
const int LCD_D5 = 4;
const int LCD_D6 = 3;
const int LCD_D7 = 2;
const int LCD_COLS = 16;
const int LCD_ROWS = 2;

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// Rotary encoder configuration
const int encoderPinA = 9;
const int encoderPinB = 10;

Encoder encoder(encoderPinA, encoderPinB);
volatile long encoderPos = 0;
volatile long prevEncoderPos = 0;

// Progress bar configuration
const int progressBarWidth = LCD_COLS; // Adjust according to your LCD

void setup() {
  Serial.begin(9600);
  lcd.begin(LCD_COLS, LCD_ROWS);
  attachInterrupt(digitalPinToInterrupt(encoderPinA), handleEncoderInterrupt, CHANGE);
}

void updateProgressBarDown(int percentage) {
  lcd.setCursor(0, 1);
  for (int i = 0; i < progressBarWidth; i++) {
    if (i < percentage) {
      lcd.write(255);
    } else {
      lcd.print(" ");
    }
  }
}

void updateProgressBarUp(int percentage) {
  lcd.setCursor(0, 0);
  for (int i = 0; i < progressBarWidth; i++) {
    if (i < percentage) {
      lcd.write(255);
    } else {
      lcd.print(" ");
    }
  }
}

void handleEncoderInterrupt() {
  encoderPos += (digitalRead(encoderPinB) == HIGH) ? 1 : -1;
  encoderPos = constrain(encoderPos, 0, 100);
}

void loop() {
  encoderPos = encoder.read();
  
  if(encoderPos > 100){
    encoder.write(100);
  }
  if(encoderPos < 0){
    encoder.write(0);
  }
  
  if (encoderPos != prevEncoderPos) {
    // Update progress bar
    int percentage = map(encoderPos, 0, 100, 0, progressBarWidth);
    Serial.println(percentage); //To check
    updateProgressBarDown(percentage);
    updateProgressBarUp(percentage);
    
    prevEncoderPos = encoderPos;
  }
}
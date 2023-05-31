#include <LiquidCrystal_I2C.h>

// Set the LCD address and dimensions
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.begin(16, 2);  // Initialize the LCD
  
  // Display a custom loading bar character
  byte loadingBar[8] = {
    B00000,
    B00001,
    B00011,
    B00111,
    B01110,
    B11100,
    B11000,
    B10000
  };
  
  lcd.createChar(0, loadingBar);  // Load the custom character
  lcd.clear();
}

void loop() {
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 0);
    lcd.write((byte)0);  // Display the custom character
    
    // Adjust the delay time according to your preference
    delay(200);
  }
  
  lcd.clear();  // Clear the LCD after the loading sequence
}

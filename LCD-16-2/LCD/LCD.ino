#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  // Define the LCD object and pin connections

int delayTime = 100; // Delay time for each progress step (10 seconds divided by the total number of progress steps)

void setup() {
  lcd.begin(16, 2);  // Initialize the LCD with 16 columns and 2 rows
  lcd.clear();  // Clear the LCD
}

void bar_up() {
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 0);
    lcd.write(255);
    lcd.setCursor(i, 1);
    lcd.write(255);  // Display a filled block character

    delay(delayTime);  // Wait for the specified delay time
  }
}

void bar_down() {
  for (int i = 16; i > 0; i--) {
    lcd.setCursor(i, 0);
    lcd.write(255);
    lcd.setCursor(i, 1);
    lcd.write(255);  // Display a filled block character
    
    delay(delayTime);  // Wait for the specified delay time
  }
}

void loop() {
  
  bar_up();
  delay(100);
  Print("hi");

  lcd.clear();  // Clear the LCD after the progress bar completes
  delay(100);  // Wait for 1 second before the next iteration (optional)
  }
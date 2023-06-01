#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  // Define the LCD object and pin connections

void setup() {
  lcd.begin(16, 2);  // Initialize the LCD with 16 columns and 2 rows
  lcd.clear();  // Clear the LCD
}

void loop() {
  int totalProgress = 16;  // Total number of progress steps (number of columns in the LCD)
  int delayTime = 10000 / totalProgress;  // Delay time for each progress step (10 seconds divided by the total number of progress steps)
  
  for (int i = 0; i < totalProgress; i++) {
    lcd.setCursor(i, 0);
    lcd.setCursor(i, 1);
    lcd.write(255);  // Display a filled block character
    
    delay(delayTime);  // Wait for the specified delay time
  }
  
  lcd.clear();  // Clear the LCD after the progress bar completes
  delay(1000);  // Wait for 1 second before the next iteration (optional)
}
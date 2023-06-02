#include <LiquidCrystal.h>

// LCD pin configuration
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Custom bar characters
byte bar_empty[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte bar_full[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

// Helper function to display the bar
void displayBar(int bar_length) {
  lcd.createChar(0, bar_empty);
  lcd.createChar(1, bar_full);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write((byte)0);

  for (int i = 0; i < bar_length; i++) {
    lcd.write((byte)1);
  }

  lcd.setCursor(16, 0);
  lcd.write((byte)0);
}

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  for (int i = 0; i <= 16; i++) {
    displayBar(i);
    delay(200);
  }

  for (int i = 16; i >= 0; i--) {
    displayBar(i);
    delay(200);
  }

  delay(1000);
}
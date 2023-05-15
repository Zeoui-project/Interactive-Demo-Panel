#include <FastLED.h>
#define NUM_LEDS 60    // Number of LEDs in the strip
#define LED_PIN 6      // Pin connected to the DI pin of the WS2812B LED
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();
  delay(1000);
}
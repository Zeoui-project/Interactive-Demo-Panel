#include <Encoder.h>

#define ENCODER_PIN1 9
#define ENCODER_PIN2 10  

Encoder encoder(ENCODER_PIN1, ENCODER_PIN2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int encoderValue = encoder.read()/4;
  if (encoderValue > 1) {
    encoderValue = 1;
  } else if (encoderValue < -1) {
    encoderValue = -1;
  }

  Serial.println(encoderValue);
}
#include <AccelStepper.h>

//────Steppermotoren
AccelStepper stepper_BASE(AccelStepper::DRIVER, 2, 5);
AccelStepper stepper_WRIST(AccelStepper::DRIVER, 7, 8);

//────Potentiometer
const int POT_BASE  = 33;
const int POT_WRIST = 39;

//────Vlotte bewegings functie
int smoothRead(int potPin) {
  int sum = 0;
  for (int i = 0; i < 16; i++) {
    sum += analogRead(potPin);
  }
  return sum / 16;
}

//────Draaiing van de stepper motor in een functie
void STEPPER_DRAAIING(AccelStepper &stepper, int potPin) {
  int potVal = smoothRead(potPin);
  long target = map(potVal, 0, 4095, 0, 200);
  if (abs(stepper.currentPosition() - target) > 2) {
    stepper.moveTo(target);
  }
  stepper.run();
}

void setup() {
  analogReadResolution(12); // van 10bit naar 12 bit

  stepper_BASE.setMaxSpeed(600);
  stepper_BASE.setAcceleration(300);
  stepper_WRIST.setMaxSpeed(600);
  stepper_WRIST.setAcceleration(300);
}

void loop() {
  STEPPER_DRAAIING(stepper_BASE,  POT_BASE);
  STEPPER_DRAAIING(stepper_WRIST, POT_WRIST);
}
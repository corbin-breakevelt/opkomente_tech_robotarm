#include <ESP32Servo.h>
#include <Adafruit_PWMServoDriver.h>
#include <AccelStepper.h>

//────PCA9685
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

//────Servo limieten per kanaal (40°-140°)
const int MIN_SHOULDER = 150;  // ~40°
const int MAX_SHOULDER = 600;  // ~140°

const int MIN_ELBOW    = 200;
const int MAX_ELBOW    = 500;

const int MIN_GRIPPER  = 150;
const int MAX_GRIPPER  = 600;

//────PCA9685 kanalen
const int CH_SHOULDER = 0;
const int CH_ELBOW    = 1;
const int CH_GRIPPER  = 2;

//────Steppermotoren
AccelStepper stepper_BASE(AccelStepper::DRIVER, 2, 5);
AccelStepper stepper_WRIST(AccelStepper::DRIVER, 16, 17);

//────Potentiometer servo's
const int POT_SHOULDER = 34; //rotatie shoulder gewricht (servo)
const int POT_ELBOW    = 35; //rotatie elleboog (servo)
const int POT_GRIPPER  = 32; //openen en dichtgaan van de gripper (servo)

//────Potentiometer steppers
const int POT_BASE  = 33; //rotatie van de volledige arm (stepper)
const int POT_WRIST = 39; //rotatie van de pols (stepper)

//────Vlotte bewegings functie
int smoothRead(int potPin) {
  int sum = 0;
  for (int i = 0; i < 16; i++) {
    sum += analogRead(potPin);
  }
  return sum / 16;
}

//────Draaiing van de servo motor in een functie
void SERVO_DRAAIING(int channel, int potPin, int minPulse, int maxPulse) {
  int POT_VAL = smoothRead(potPin);
  int pulseWidth = map(POT_VAL, 0, 4095, minPulse, maxPulse);
  pulseWidth = constrain(pulseWidth, minPulse, maxPulse);
  pwm.setPWM(channel, 0, pulseWidth);
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
  analogReadResolution(12); // van 10bit naar 12bit

  //────servos
  Wire.begin(21, 22);
  pwm.begin();
  pwm.setPWMFreq(50);

  //────steppermotoren
  stepper_BASE.setMaxSpeed(600);
  stepper_BASE.setAcceleration(300);
  stepper_WRIST.setMaxSpeed(600);
  stepper_WRIST.setAcceleration(300);
}

void loop() {
  //────servo's aansturen
  SERVO_DRAAIING(CH_SHOULDER, POT_SHOULDER, MIN_SHOULDER, MAX_SHOULDER);
  SERVO_DRAAIING(CH_ELBOW,    POT_ELBOW,    MIN_ELBOW,    MAX_ELBOW);
  SERVO_DRAAIING(CH_GRIPPER,  POT_GRIPPER,  MIN_GRIPPER,  MAX_GRIPPER);

  //────steppers aansturen
  STEPPER_DRAAIING(stepper_BASE,  POT_BASE);
  STEPPER_DRAAIING(stepper_WRIST, POT_WRIST);

  delay(20);
}

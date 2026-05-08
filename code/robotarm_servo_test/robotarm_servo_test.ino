 #include <ESP32Servo.h>
#include <Adafruit_PWMServoDriver.h>


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


//────potentiometer
int POT_SHOULDER = 34; //rotatie shouder gewricht (servo)
int POT_ELBOW = 35; //rotatie elleboog (servo)
int POT_GRIPPER = 32; //openen en dichtgaan van de gripper (servo)

//────Draaiing van de servo motor in een functie
void SERVO_DRAAIING(int channel, int potPin, int minPulse, int maxPulse){

  int POT_VAL = analogRead(potPin);
  int pulseWidth = map(POT_VAL, 0, 4095, minPulse, maxPulse);
  pulseWidth = constrain(pulseWidth,minPulse,maxPulse);
  pwm.setPWM(channel, 0, pulseWidth);

}

void setup() {
analogReadResolution(12);
//────servos
pinMode(POT_SHOULDER, INPUT);
pinMode(POT_ELBOW, INPUT);;
pinMode(POT_GRIPPER, INPUT);

Wire.begin(21, 22);
pwm.begin();
pwm.setPWMFreq(50);
}

void loop() {
SERVO_DRAAIING(CH_SHOULDER, POT_SHOULDER, MIN_SHOULDER, MAX_SHOULDER);
SERVO_DRAAIING(CH_ELBOW,    POT_ELBOW,    MIN_ELBOW,    MAX_ELBOW);
SERVO_DRAAIING(CH_GRIPPER,  POT_GRIPPER,  MIN_GRIPPER,  MAX_GRIPPER);
delay(20);
}


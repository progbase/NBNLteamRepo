enum GARAGE_PROTOCOL {
  GET_PERSON_MOTION_STATUS, // expects to receive a 1 - there is motion, 0 - there is no motion
  GET_CAR_MOTION_STATUS, // expects to receive a 1 - there is a car moving, 0 - there is no car moving
  GET_CAR_PRESENCE_STATUS, // expects to receive a 1 - there is a car in the garage, 0 - there is not
  GET_DOOR_STATUS, // expects to receive 1 - the door is opened, 0 - the door is closed
  SET_DOOR_OPEN, // expects to receive 1 if opening, 0 if already
  SET_DOOR_CLOSE // expects to receive 1 if closing, 0 if already
};
#include <Stepper.h>
#include <NewPing.h>
//Stepper
//---( Number of steps per revolution of INTERNAL motor in 4-step mode )---
const int nStepsPerMotorRevolution = 32;
//---( Steps per OUTPUT SHAFT of gear reduction )---
const int nStepsPerOutputRevolution = 32 * 64;  //2048
const float nCircles = 1.3;
Stepper small_stepper(nStepsPerMotorRevolution, 10, 8, 9, 11); // STEPPER CREATION

const int maxLightVal = 185;
const int minLightVal = 10;
const int maxDistance = 400;
// PINS
const int pResistor1 = A1; // Photoresistor 
const int pResistor2 = A2;
const int pMotionSencor = 2;
const int pEcho = 6;
const int pTrigger = 7;
const int pLight = 5;

const int doorStepOpen = -1;
// GLOBALS
int isMotionDetected = 0;
int isPresent = 0;
int isCarMotion = 0;
int isDoorOpened = 0;
NewPing sonar(pTrigger, pEcho, maxDistance);

void setup() {
  Serial.begin(9600); // BAUD RATE
  pinMode(pResistor1, INPUT);
  pinMode(pResistor2, INPUT);
  pinMode(pMotionSencor, INPUT);
  pinMode(pLight, OUTPUT);

}

void loop() {
  if (Serial.available() > 0)
  {
    // read the incoming byte:
    char received = Serial.read();
    message_proccess(received);
  }
  int valRes1 = analogRead(pResistor1);
  int valRes2 = analogRead(pResistor2);
  int valMotion = digitalRead(pMotionSencor);
  setCarPresence(valRes1, valRes2);
  setMotionDetection(valMotion);
  checkLights();
}
void checkLights()
{
  if(isCarMotion)
    analogWrite(pLight, maxLightVal);
  else if(isMotionDetected)
    analogWrite(pLight, minLightVal);
  else
    analogWrite(pLight, LOW);
}
void setCarPresence(int valRes1, int valRes2)
{
  if (abs(valRes1 - valRes2) < 40)
    isPresent = 1;
  else
    isPresent = 0;
}
void setMotionDetection(int valMotion)
{
  float dist = sonar.ping() / US_ROUNDTRIP_CM;
  if (dist > 22)
    isCarMotion = 0;
  else if(dist > 1)
    isCarMotion = 1;
  if (valMotion == HIGH)
    isMotionDetected = 1;
  else
    isMotionDetected = 0;
}
void message_proccess(char message)
{
  switch (message)
  {
    case GET_PERSON_MOTION_STATUS: case '0':
      {
        Serial.write(isMotionDetected);
      } break;
    case GET_CAR_MOTION_STATUS:
      {
        Serial.write(isCarMotion);
      } break;
    case GET_CAR_PRESENCE_STATUS: case '2':
      {
        Serial.write(isPresent);
      } break;
    case GET_DOOR_STATUS:
      {
        Serial.write(isDoorOpened);
      } break;
    case SET_DOOR_OPEN:
      {
        if (isDoorOpened)
        {
          Serial.write(0);
          break;
        }
        Serial.write(1);
        isDoorOpened = 1;
        stepperTurn(doorStepOpen);
      } break;
    case SET_DOOR_CLOSE:
      {
        if (isDoorOpened == 0)
        {
          Serial.write(0);
          break;
        }
        Serial.write(1);
        isDoorOpened = 0;
        stepperTurn(-doorStepOpen);
      } break;
    default:
      Serial.println("Shit happens");
  }
}
void stepperTurn(int clockwise)
{
  int stepsToTake =  clockwise * nStepsPerOutputRevolution * nCircles; // Rotate CCW OR CW OR 0 for 1 turn
  small_stepper.setSpeed(600);  // 700 a good max speed??
  small_stepper.step(stepsToTake);
} 

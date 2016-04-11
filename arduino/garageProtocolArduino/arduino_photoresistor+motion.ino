enum GARAGE_PROTOCOL {
  GET_PERSON_MOTION_STATUS, // expects to receive a 1 - there is motion, 0 - there is no motion
  GET_CAR_MOTION_STATUS, // expects to receive a 1 - there is a car moving, 0 - there is no car moving
  GET_CAR_PRESENCE_STATUS, // expects to receive a 1 - there is a car in the garage, 0 - there is not
  GET_DOOR_STATUS, // expects to receive 1 - the door is opened, 0 - the door is closed
  SET_DOOR_OPEN, // expects to receive 1 if opening, 0 if already
  SET_DOOR_CLOSE // expects to receive 1 if closing, 0 if already
};
const int pResistor1 = A0; // Photoresistor at Arduino analog pin A0
const int pResistor2 = A1;

int inputPin = 2;  // pir INPUT
int isMotionDetected = 0;  // ???????? ?????? ?????????, ???????????, ??? ???????? ???

int val = 0;  // ?????????? ??? ?????? ????????? ????
int value1;          // Store value from photoresistor (0-1023)
int value2;
int isPresent = 0;
void setup() {
  Serial.begin(9600);
  pinMode(pResistor1, INPUT);// Set pResistor - A0 pin as an input (optional)
  pinMode(pResistor2, INPUT);
  pinMode(inputPin, INPUT);  // ????????? ?????? ? ???????? INPUT

}

void loop() {
  if (Serial.available() > 0)
  {
    // read the incoming byte:
    char received = Serial.read();
    message_proccess(received);
  }
  value1 = analogRead(pResistor1);
  value2 = analogRead(pResistor2);
  if ((value1 - value2) < 400)
    isPresent = 1;
  else
    isPresent = 0;

  val = digitalRead(inputPin);  // ????????? ???????? ? ???????
  if (val == HIGH)  // ?????????, ????????????? ?? ????????? ???????? HIGH
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
          Serial.write(1);
        } break;
      case GET_CAR_PRESENCE_STATUS: case '2':
        {
          Serial.write(isPresent);
        } break;
      case GET_DOOR_STATUS:
        {
          Serial.write(3);
        } break;
      case SET_DOOR_OPEN:
        {
          Serial.write(4);
        } break;
      case SET_DOOR_CLOSE:
        {
          Serial.write(5);
        } break;
      default:
        Serial.println("Shit happens");
    }
  }
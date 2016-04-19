#include <NewPing.h>

 
#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 400
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 
void setup() {
  Serial.begin(9600);
}
 
void loop() {
  delay(100);
  int firstDis = sonar.ping();
  delay(2500);
  int secondDis = sonar.ping();
  if ((firstDis - secondDis) > 7)
    digital.write(1);
  else
    digital.write(0);
  Serial.println("Ping: ");
  Serial.println(firstDis / US_ROUNDTRIP_CM);
  Serial.println("cm");
}

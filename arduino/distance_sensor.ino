#include <NewPing.h>

 
#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 400
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 
void setup() {
  Serial.begin(9600);
}
 
void loop() {
  delay(500);
  int uS = sonar.ping();
  Serial.println("Ping: ");
  Serial.println(uS / US_ROUNDTRIP_CM);
  Serial.println("cm");
}
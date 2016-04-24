/* Use a photoresistor (or photocell) to turn on an LED in the dark
   More info and circuit schematic: http://www.ardumotive.com/how-to-use-a-photoresistor-en.html
   Dev: Michalis Vasilakis // Date: 8/6/2015 // www.ardumotive.com */
   

//Constants
const int pResistor1 = A0; // Photoresistor at Arduino analog pin A0
const int pResistor2 = A1;

//Variables
int value1;          // Store value from photoresistor (0-1023)
int value2;

void setup(){
  Serial.begin(9600);  //Begin serial communcation
 pinMode(pResistor1, INPUT);// Set pResistor - A0 pin as an input (optional)
 pinMode(pResistor2, INPUT);
}

void loop(){
  value1 = analogRead(pResistor1);
  value2 = analogRead(pResistor2);
  Serial.println(value1 - value2);
}

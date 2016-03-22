#include <Stepper.h>

/*-----( Declare Constants, Pin Numbers )-----*/
//---( Number of steps per revolution of INTERNAL motor in 4-step mode )---
#define STEPS_PER_MOTOR_REVOLUTION 32   

//---( Steps per OUTPUT SHAFT of gear reduction )---
#define STEPS_PER_OUTPUT_REVOLUTION 32 * 64  //2048  
 

/*-----( Declare objects )-----*/
// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to

//The pin connections need to be 4 pins connected
// to Motor Driver In1, In2, In3, In4  and then the pins entered
// here in the sequence 1-3-2-4 for proper sequencing
Stepper small_stepper(STEPS_PER_MOTOR_REVOLUTION, 8, 9, 10, 11);
int received;
/*-----( Declare Variables )-----*/
int  Steps2Take;
int work = 1;
void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
}/*--(end setup )---*/

void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (Serial.available() > 0) 
  {
    // read the incoming byte:
    received = Serial.read();
    Serial.println(received, DEC);
    switch(received)
    {
      case '0': case 0:
      {
        work = 0;
      }break;
      case '1': case 1:
      {
        work = 1;
      }break;
    }
   }
  if(work)
  {
    Steps2Take  =  STEPS_PER_OUTPUT_REVOLUTION/10;  // Rotate CCW 1 turn  
    small_stepper.setSpeed(600);  // 700 a good max speed??
    small_stepper.step(Steps2Take);
  }
  delay(1000);

}/* --(end main loop )-- */

/* ( THE END ) */


#include <SoftwareSerial.h>
#include <Servo.h>

// C++ code
//
/*
  Robotic Arm 

  by Youssouf BB <https://github.com/j2B237/robotic_Arm>
  This project is in the public domain.

  modified 23 August 2021  by Youssouf BB
*/

// Define bluetooth RECEIVER TRANSMETTER PINS
#define BTRX 1
#define BTTX 0

// Define all servos pins. Always choose PWM Pins
#define pinServo1 3
#define pinServo2 5
#define pinServo3 6
#define pinServo4 9
#define pinServo5 10


// Create an instance of bluetooth adaptor
SoftwareSerial SerialBT(BTTX, BTRX);


// Create instance of servo motor
Servo myServo1;
Servo myServo2;
Servo myServo3;
Servo myServo4;
Servo myServo5;


// Declare servo motor velocity speed
// 10ms => Fast | 15ms => Medium | 20ms => Slow
int s1Vel = 15;
int s2Vel = 20;
int s3Vel = 20;
int s4Vel = 15;
int s5Vel = 20;

// Declare variable to save current servo'position
int s1Act, s2Act, s3Act, s4Act, s5Act;

// Declare variable to save last servo position
int s1Ant, s2Ant, s3Ant, s4Ant, s5Ant;


int index = 0;
int velG = 25;
String bts;
int btsToInt;

void setup()
{
  // Initialze serial monitor
  Serial.begin(9600);
  
  // Initialize bluetooth communication speed
  SerialBT.begin(9600);
  Serial.println("Bluetooth connection established");
  SerialBT.setTimeout(10);		// Wait for a new serial data
  
  
  // Initialize servo pin connection rotation range
  myServo1.attach(pinServo1, 0, 180);
  myServo2.attach(pinServo2, 45, 180);
  myServo3.attach(pinServo3, 0, 180);
  myServo4.attach(pinServo4, 0, 180);
  myServo5.attach(pinServo5, 0, 180);
  
  // Define starter position for each sevo
  s1Ant = 0;
  myServo1.write(s1Ant);
  
  s2Ant = 45;
  myServo2.write(s2Ant);

  s3Ant = 0;
  myServo3.write(s3Ant);

  s4Ant = 90;
  myServo4.write(s4Ant);

  s5Ant = 70;
  myServo5.write(s5Ant);
}

void loop()
{
  // Data are available through bluetooth line
  if (SerialBT.available() > 0)
  {
  
  	bts = SerialBT.readStringUntil("\n");
    btsToInt = bts.toInt();
    
    
    // Control base servo between [5000, 5180]
    if (btsToInt >= 5000 && btsToInt < 5180)
    {
    	s1Act = map(btsToInt, 5000, 5180, 0, 180);
      
      	if (s1Ant > s1Act)
        {
        	for(int j=s1Ant; j>=s1Act; j--)
            {
            	myServo1.write(j);
              	delay(s1Vel);
            }
        }
      	else
        {
        	for(int j=s1Ant; j<=s1Act; j++)
            {
            	myServo1.write(j);
              	delay(s1Vel);
            }
        }
      	s1Ant = s1Act;		// Update servo current position
    } // End servo1
    
    
    // Control shoulder servo between [4000, 4180]
    if (btsToInt >= 4000 && btsToInt < 4180)
    {
    
    	s2Act = map(btsToInt, 4000, 4180, 45, 180);
      	
      if (s2Ant > s2Act)
      {
      	for (int j=s2Ant; j>=s2Act; j--)
        {
        	myServo2.write(j);
          	delay(s2Vel);
        }
      }
      else
      {
      	for (int j=s2Ant; j<=s2Act; j++)
        {
        	myServo2.write(j);
          	delay(s2Vel);  
        }
      }
    	s2Ant = s2Act;
    } // End servo2
    
    
    // Control elbow servo between [3000, 3180]
    if (btsToInt > 3000 && btsToInt < 3180)
    {
    
    	  s3Act = map(btsToInt, 3000, 3180, 0, 180);
      	if (s3Ant > s3Act)
        {
        	for(int j=s3Ant; j>=s3Act; j--)
            {
            	myServo3.write(j);
              	delay(s3Vel);
            }
        }
      	else
        {
          	for(int j=s3Ant; j<=s3Act; j++)
            {
            	myServo3.write(j);
              	delay(s3Vel);
            }
        
        }
      	s3Ant = s3Act;
    }	//End servo3
    
    
    // Control Wirst servo between [2000, 2180]
    if (btsToInt >= 2000 && btsToInt < 2180)
    {
    	s4Act = map(btsToInt, 2000, 2180, 0, 180);
      	
      	if(s4Ant > s4Act)
        {
        	for(int j=s4Ant; j>=s4Act; j--)
            {
            	myServo4.write(j);
              	delay(s4Vel);
            }
        }
      	else
        {
        	for(int j=s4Ant; j<=s4Act; j++)
            {
            	myServo4.write(j);
              	delay(s4Vel);
            }
        }
    
    	s4Ant = s4Act;
    }// End servo4
    
    
    // Control Gripper servo between [1000, 1180]
    if (btsToInt >= 1000 && btsToInt < 1180)
    {
    	s5Act = map(btsToInt, 1000, 1180, 0, 180);
      	
      	if(s5Ant > s5Act)
        {
        	for (int j=s5Ant; j>=s5Act; j--)
            {
            	myServo5.write(j);
              	delay(s5Vel);
            }
        }
      	else
        {
        	for (int j=s5Ant; j<=s5Act; j++)
            {
            	myServo5.write(j);
              	delay(s5Vel);
            }
        }
    
    	s5Ant = s5Act;
    }
  
  } //Enf if 
  
} // End loop

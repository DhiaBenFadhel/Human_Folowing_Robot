//include the library code:
#include<NewPing.h>          
#include<Servo.h>            
#include<AFMotor.h>          

#define RIGHT_OUT_PIN A2 // Output pin for right IR sensor driver (A2)
#define LEFT_OUT_PIN A4  // Output pin for left IR sensor driver (A4)              
#define TRIGGER_PIN A1        // Trigger pin connected to analog pin A1 of Arduino Uno
#define ECHO_PIN A0           // Echo pin connected to analog pin A0 of Arduino Uno
#define MAX_DISTANCE 200      // Maximum ping distance

unsigned int distance = 0;    //Variable to store ultrasonic sensor distance
unsigned int Right_Value = 0; //Variable to store Right IR sensor value
unsigned int Left_Value = 0;  //Variable to store Left IR sensor value

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);  //NewPing setup of pins and maximum distance

//create motor objects
AF_DCMotor Motor1(1);
AF_DCMotor Motor2(2);

 Servo myservo; //create servo object to control the servo
 int pos=0;     //variable to store the servo position
  

void setup() { // the setup function runs only once when power on the board or reset the board:
   Serial.begin(9600); //initialize serial communication at 9600 bits per second:
   myservo.attach(10); // servo attached to pin 10 of Arduino UNO
  // Set IR sensor output pins as inputs
  pinMode(RIGHT_OUT_PIN, INPUT);
  pinMode(LEFT_OUT_PIN, INPUT);
  {
    for(pos = 90; pos <= 180; pos += 1){    // goes from 90 degrees to 180 degrees:
      myservo.write(pos);                   //tell servo to move according to the value of 'pos' variable:
      delay(15);                            //wait 15ms for the servo to reach the position:
    }
    for(pos = 180; pos >= 0; pos-= 1) {     // goes from 180 degrees to 0 degrees:
      myservo.write(pos);                   //tell servo to move according to the value of 'pos' variable:
      delay(15);                            //wait 15ms for the servo to reach the position:
    }
    for(pos = 0; pos<=90; pos += 1) {       //goes from 0 degrees to 90 degrees:
      myservo.write(pos);                   //tell servo to move according to the value of 'pos' variable:
      delay(15);                            //wait 15ms for the servo to reach the position:
    }
  }
}


// the lope function runs forever
void loop() {                            
 
  delay(50);                                        //wait 50ms between pings:
  distance = sonar.ping_cm();                       //send ping, get distance in cm and store it in 'distance' variable:
  Serial.print("distance");                  
  Serial.println(distance);                         // print the distance in serial monitor:
  Right_Value = digitalRead(RIGHT_OUT_PIN);             // read the value from Right IR sensor:
  Left_Value = digitalRead(LEFT_OUT_PIN);               // read the value from Left IR sensor:
 
  Serial.print("RIGHT");                      
  Serial.println(Right_Value);                      // print the right IR sensor value in serial monitor:
  Serial.print("LEFT");                      
  Serial.println(Left_Value);                       //print the left IR sensor value in serial monitor:

  if((distance > 1) && (distance < 15)){            //check wheather the ultrasonic sensor's value stays between 1 to 15.
                                                  //If the condition is 'true' then the statement below will execute:
  //Move Forward:
  Motor1.setSpeed(150);  //define motor1 speed:
  Motor1.run(BACKWARD);   //rotate motor1 clockwise:
  Motor2.setSpeed(150);  //define motor2 speed:
  Motor2.run(FORWARD);   //rotate motor2 clockwise:
  delay(150);

  }else if((Right_Value==0) && (Left_Value==1)) {   //If the condition is 'true' then the statement below will execute:
  //Turn Left                                                
  Motor1.setSpeed(150);  //define motor1 speed:
  Motor1.run(FORWARD);   //rotate motor1 clockwise:
  Motor2.setSpeed(150);  //define motor2 speed:
  Motor2.run(BACKWARD);   //rotate motor2 clockwise:
  delay(150);
  }else if((Right_Value==1)&&(Left_Value==0)) {     //If the condition is 'true' then the statement below will execute:
  //Turn Right
  Motor1.setSpeed(150);  //define motor1 speed:
  Motor1.run(BACKWARD);  //rotate motor1 anticlockwise:
  Motor2.setSpeed(150);  //define motor2 speed:
  Motor2.run(FORWARD);  //rotate motor2 anticlockwise:
  delay(150);
  }else if(distance > 15) {                          //If the condition is 'true' then the statement below will execute:
  //Stop
  Motor1.setSpeed(0);    //define motor1 speed:
  Motor1.run(RELEASE);   //stop motor1:
  Motor2.setSpeed(0);    //define motor2 speed:
  Motor2.run(RELEASE);   //stop motor2:
  }
}


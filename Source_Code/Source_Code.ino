/*  PIR Motion Sensor With Servo Motor
 * 
 *  GitHub URL - https://github.com/narayanvyas/Arduino-PIR-Motion-Sensor-SC-SR501-With-Servo-Motor
 * 
 *  Developed By Web Dev Fusion
 *  URL - https://www.webdevfusion.com
 *  
 *  Designed By S-Kit
 *  
 * Components
 * ----------
 *  - Arduino Uno
 *  - Infrared Motion Sensor
 *  - Ultrasonic Distance Sensor
 *  - An LED
 *  - A 220 Ohm resistor for the LED
 *  - A Buzzer
 *  - A Servo Motor
 *  
 *  Libraries
 *  ---------
 *  - None
 *
 * Connections
 * -----------
 *  Break out    |    Arduino Uno
 *  --------------------------------------------
 *      PIR VCC            |        5V
 *      PIR GND            |        GND
 *      PIR OUT            |        3
 *      Servo VCC VCC      |        5V
 *      Servo GND          |        GND
 *      Servo Out          |        5
 *      Buzzer GND         |        GND
 *      Buzzer Out         |        8
 *      
 * Also connect an LED to simulate a controlled device. 
 *           220 Ohm
 *    3 ----/\/\/\/\----(LED |)----GND
 *  
 */

#include <Servo.h>      // Loading Servo Motor Header Files
 
int ledPin   = 4;       // choose the pin for the LED
int inputPin = 3;       // choose the input pin (for PIR sensor)
int pirState = LOW;     // we start, assuming no motion detected
int val      = 0;       // variable for reading the pin status
int buzzer = 8;         // choose pin for the buzzer
int servoPin = 5;       // Servo Pin

//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 30; //This time is in seconds
Servo Servo1;             // creating servo object
 
void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
  pinMode(buzzer, OUTPUT);     // declare buzzer as output
  Servo1.attach(servoPin);     // attaching servo pin
 
  Serial.begin(9600);
  Serial.println("Waiting for the sensor to warm up.");
  Serial.println("SENSOR ACTIVE");
}
 
void loop(){
  val = digitalRead(inputPin);  // read input value

  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    tone(buzzer, 1000);
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
      Servo1.write(180);
      Serial.println("Arm Moved");
      delay(5000);
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned off
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
      noTone(buzzer);
      Servo1.write(0);
      Serial.println("Arm Moved Back To Original Stage");
    }
  }
}

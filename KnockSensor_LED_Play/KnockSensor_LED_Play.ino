/*
  Analog input, analog output, serial output

 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.

 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground

CCode modified from Tom Igoe
 created 29 Dec. 2008
 modified 27 Feb 2018
 by Clint Posey

 This example code is in the public domain.

 */

// These constants won't change.  They're used to give names
// to the pins used:
const int SensorInPin = A0;  // Analog input pin that the sensor is attached to
const int LEDOutPin = 13; // Analog output pin that the LED is attached to 

int sensorValue = 0;        // value read from the pot
int outputValue = LOW;        // value output to the PWM (analog out)
int pillstate = 0;          // states whether or not pill is inside device
//int LEDstate = LOW;

void setup() {
 // initialize serial communications at 9600 bps:
Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(SensorInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);
 if(sensorValue > 750);{
    pillstate = 1;
    outputValue = LOW;
    
   };
   if(sensorValue < 250);{
    delay(300);
    pillstate = 0;
    outputValue = HIGH;
    };

if(pillstate = 0 && sensorValue > 700);{
    pillstate = 1;
    outputValue = LOW;
 };
 
    
  // change the analog out value:
  analogWrite(LEDOutPin, outputValue);
  

  // print the results to the serial monitor:
Serial.print("sensor = ");
Serial.print(sensorValue);
Serial.print("\t output = ");
Serial.println(outputValue);

  // wait 1 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(.75);
}

/*This program implements a simulation of a networked wearable device that tracks whether or 
 * not a medication tablet is present in a wearable device. Binary state is transmitted to 
 * Android application to indicate presence or absence of medication within device. Note presence
 * or absence of tablet is determined in the knock sensor code

*/

const int Dose1MissedPin = 12; // LED to show that the 1st dose has been missed
const int Dose1TakenPin = 13;  // LED to show that the 1st dose has been taken
const int Dose2MissedPin = 10; // LED to show that the 1st dose has been missed
const int Dose2TakenPin = 11;  // LED to show that the 2nd dose has been taken
const int btnPin1 = 7;  // push button - Dose 1
const int btnPin2 = 6;  // push button - Dose 2

char data = 0;                //Variable for storing received data

// set boolean variables to monitor status of pills
boolean Pill1 = false;
boolean Pill2 = false;

// variable for buttons
int btnState1 = 0;
int btnState2 = 0;
int lastbtnState1 = 0;
int lastbtnState2 = 0;
int btn1pushcounter = 0;
int btn2pushcounter = 0;

void setup() 
{
  Serial.begin(9600);         //Sets the data rate in bits per second (baud) for serial data transmission
  
  //Set pins
  pinMode(Dose1MissedPin, OUTPUT);
  pinMode(Dose1TakenPin, OUTPUT); 
  pinMode(Dose2MissedPin, OUTPUT);
  pinMode(Dose2TakenPin, OUTPUT);
  pinMode(btnPin1, INPUT);
  pinMode(btnPin2, INPUT);

}
void loop() {
  
  // first we check the status of the doses
 btnState1 = digitalRead(btnPin1);
 btnState2 = digitalRead(btnPin2);

 // if button #1 is clicked set button counter for pill1
  if (btnState1 != lastbtnState1) {
      if (btnState1 == HIGH) {
       btn1pushcounter++;
  } else {
    }
    delay(50);
  }
    // save the current state as the last state,
    //for next time through the loop
    lastbtnState1 = btnState1;
    
 // if button #2 is clicked set button counter for pill2
  if (btnState2 != lastbtnState2) {
      if (btnState2 == HIGH) {
       btn2pushcounter++;
  } else {
    }
    delay(50);
  }
    // save the current state as the last state,
    //for next time through the loop
    lastbtnState2 = btnState2;

    //set booleans for button1
    if (btn1pushcounter % 2 == 0) {
      digitalWrite(Dose1TakenPin, HIGH);
      //Serial.println("Pill 1 Present");
      //Serial.println("\n");
      Pill1 = true;
  } else {
    digitalWrite(Dose1TakenPin, LOW);
    //Serial.println("Pill 1 Absent");
    //Serial.println("\n");
    Pill1 = false;
  }

if (btn2pushcounter % 2 == 0) {
      digitalWrite(Dose2TakenPin, HIGH);
      //Serial.println("Pill 2 Present");
      //Serial.println("\n");
      Pill2 = true;
  } else {
    digitalWrite(Dose2TakenPin, LOW);
    //Serial.println("Pill 2 Absent");
    //Serial.println("\n");
    Pill2 = false;
  }
    
  if(Serial.available() > 0)  // Send data only when you receive data:
  {
    data = Serial.read();      //Read the incoming data and store it into variable data
    Serial.print(data);        //Print Value inside data in Serial monitor
    Serial.print("\n");        //New line 
    
    //Checks whether value of data is equal to 1: checking to see if first dose was taken
    if(data == '1') {
      if(btnState1 == 0) {             

      //If 1st dose is detected, dose 1 was missed, blink red LED twice
      digitalWrite(Dose1MissedPin, HIGH);  
      delay(500);
      digitalWrite(Dose1MissedPin, LOW);
      delay(500);
      digitalWrite(Dose1MissedPin, HIGH);  
      delay(500);
      digitalWrite(Dose1MissedPin, LOW);
      }
      
      //If 1st dose isn't detected, dose 1 was taken, blink green LED twice
      else {       
      digitalWrite(Dose1TakenPin, HIGH);
      delay(500);   
      digitalWrite(Dose1TakenPin, LOW);
      delay(500); 
      digitalWrite(Dose1TakenPin, HIGH);
      delay(500);   
      digitalWrite(Dose1TakenPin, LOW);
      }
      } 
    }
    else if(data == '0'){       //Checks whether value of data is equal to 0

      
  //If 2nd dose is detected, dose 2 was missed, blink 2nd red LED twice
      if (btnState2 == 0) {
      digitalWrite(Dose2MissedPin, HIGH);  
      delay(500);
      digitalWrite(Dose2MissedPin, LOW);
      delay(500);
      digitalWrite(Dose2MissedPin, HIGH);  
      delay(500);
      digitalWrite(Dose2MissedPin, LOW);
      }
      
      //If 2nd dose isn't detected, dose 2 was taken, blink 2nd green LED twice
      else {       
      digitalWrite(Dose2TakenPin, HIGH);
      delay(500);   
      digitalWrite(Dose2TakenPin, LOW);
      delay(500); 
      digitalWrite(Dose2TakenPin, HIGH);
      delay(500);   
      digitalWrite(Dose2TakenPin, LOW);
      } 
    } 
  }                            

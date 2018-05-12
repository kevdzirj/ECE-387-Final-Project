//this is my final
#include <LiquidCrystal.h> //library for the LCD screen
#include <Servo.h>; //library for the servo motor
Servo myservo; 
int servoCount = 0;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //sets the pins of the LCD screen to the appropriate Arduino pins
int sup = 0;
int one = 0;
int pos = 180;
int two = 0;
int three = 0;
int count = 0;
int newCount = 0;
int sequenceOne;
int sequenceTwo;
int sequenceThree; 
int sequenceFour; 
int sequenceFive; 
int sequenceSix; 
int winner = 0;
int setFour;
int setFive;
int setSix;
int switches = 13; //pin number for the switch
int trgPinFirst = 8; //the trigger and echo are collected 4 different times but use the same two pins
int echPinFirst = 9;
int trgPinSecond = 8;
int echPinSecond = 9;
int trgPinThree = 8;
int echPinThree = 9;
int trgPinFour = 8;
int echPinFour = 9;
int times = 6; //pin of the  piezo speaker

long microsecondLOne; 
long centimeterLOne;
long microsecondLTwo;
long centimeterLTwo;
long microsecondLThree;
long centimeterLThree;
long microsecondLFour;
long centimeterLFour;


void setup() {

myservo.attach(10); //this uses the attach() to claim pin 10 as the servo motor pin
pinMode(10, OUTPUT); //the motor is an output
  
lcd.clear(); 
lcd.begin(16, 2); //sets the LCD screen to be a 16x2 character screen

pinMode(trgPinFirst, OUTPUT); 
pinMode(echPinFirst, INPUT); 
pinMode(trgPinSecond, OUTPUT); 
pinMode(echPinSecond, INPUT); 
pinMode(trgPinThree, OUTPUT); 
pinMode(echPinThree, INPUT); 
pinMode(trgPinFour, OUTPUT); 
pinMode(echPinFour, INPUT); 
pinMode(times, OUTPUT);
pinMode(switches, INPUT);

Serial.begin(9600); 
}

void loop() {
  
if(digitalRead(switches)==LOW){  //all of the code in the if executes if the switch is low
                                 //this is the code that "sets the passcode
digitalWrite(echPinFirst, LOW); 
digitalWrite(trgPinFirst, HIGH); 
delayMicroseconds(10);
digitalWrite(trgPinFirst, LOW); //starts the internal clock by sending out a "ping"

microsecondLOne = pulseIn(echPinFirst, HIGH); //records the amount of time in microseconds from leaving the sensor to hitting an object and going back to sensor
centimeterLOne= ((microsecondLOne/2)*.03436); //converts from microseconds to contimeters using speed of sound conversion and dividing by 2

if (centimeterLOne < 15 && centimeterLOne > 0 && count < 3) { //conducts when the hand placement is between 0 and 15 cm & it is not over the third hand placement
  lcd.clear();
  lcd.setCursor(0,0); //sets the cursor to 0x0 position on the LCD screen
  lcd.print("Tone:"); //prints the word tone
  lcd.setCursor(6,0); //sets the cursor to 6x0 position on the LCD screen
  lcd.print("1"); //"1" is printed to show the closest hand placement
tone(times, 100); //piezo sounds of a 100Hz freeuncy
delay(5000);
noTone(times);

if(count == 0){ //conducts if it is the first hand placement
sequenceOne = 100; //the first hand placement becomes 100
}
if(count == 1){ //conducts if it is the second hand placement
sequenceTwo = 100; //the second hand placement becomes 100
}
if(count == 2){ //conducts if it is the third hand placement
sequenceThree = 100; //the third hand placement becomes 100
}
count = count + 1; //after the process count is incremented to move onto the next hand placement
}


if (centimeterLOne < 30 && centimeterLOne > 15 && count < 3) { //hand between 15 and 30cm and not more than the third hand placement
  lcd.clear();
  lcd.setCursor(0,0);        //similar to above
  lcd.print("Tone:"); 
lcd.setCursor(6,0);
  lcd.print("2");  //a "2" is printed to show that it is the second farthest distance
tone(times, 300); //tone of 300Hz is played to differentiate tone of distance
delay(5000);
noTone(times);

if(count == 0){     //same as above except uses 300 Hz as the tone 
sequenceOne = 300; 
}
if(count == 1){
sequenceTwo = 300; 
}
if(count == 2){
sequenceThree = 300; 
}
count = count + 1;
}


if (centimeterLOne < 45 && centimeterLOne > 30 && count < 3) {  //is conducted when handplacement is between 30 and 45 centimeters & it is not more than the 3rd hand placement
  lcd.clear();  //same as above
  lcd.setCursor(0,0);
  lcd.print("Tone:"); 
lcd.setCursor(6,0);
  lcd.print("3"); //"3" is printed to display that it is the third farthest distance from the sensor
tone(times, 500); //tone of 500 Hz is played through the piezo to differentiate from other speakers
delay(5000);
noTone(times);

if(count == 0){  //similar from above except 500 Hz
sequenceOne = 500; 
}
if(count == 1){
sequenceTwo = 500; 
}
if(count == 2){
sequenceThree = 500; 
}
count  = count +1;
}
if(digitalRead(switches) == LOW && count == 3){ //conducts if it is the 4th hand placement and the switch is still on low
  lcd.clear();
  lcd.setCursor(1,1);
  lcd.print("set system"); //set system is printed to tell the person that the system is set and to hit the swithc
  delay(2500);
}
}

if(digitalRead(switches)==HIGH && sup == 0){ //conducts when the switch is high and the motor has not already spun
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("passcode?"); //asks the user for the passcode

delay(5000);
digitalWrite(trgPinSecond, HIGH); 
delayMicroseconds(10);
digitalWrite(trgPinSecond, LOW);
microsecondLTwo = pulseIn(echPinSecond, HIGH); //retrieves the amount of time the sensor takes to get to the hand placement and back
centimeterLTwo= ((microsecondLTwo/2)*.03436); //converts to centimeters
Serial.print(centimeterLTwo);

if(centimeterLTwo > 0 && centimeterLTwo < 15){ //hand placement is between 0 and 15cm
  sequenceFour = 100; //sets the tone to 100Hz
  setFour = 1; //sets the cooresponding number of tone to 1
}
if(centimeterLTwo > 15 && centimeterLTwo < 30){ //hand placement is between 15 and 30cm
  sequenceFour = 300; //sets the tone to 300Hz
  setFour = 2; //sets the cooresponding number of tone to 2
}
if(centimeterLTwo > 30 && centimeterLTwo < 45){ //hand placement is between 30 and 45cm
  sequenceFour = 500; //sets the tone to 500Hz
  setFour = 3; //sets the cooresponding number of tone to 3
}
lcd.setCursor(0,1);
lcd.print(setFour); //displays tone number
tone(times, sequenceFour); //plays the tone
delay(2500);
noTone(times);

digitalWrite(trgPinThree, HIGH); //conducts again, this time it is the second hand placement
delayMicroseconds(10);
digitalWrite(trgPinThree, LOW);
microsecondLThree = pulseIn(echPinThree, HIGH); 
centimeterLThree= ((microsecondLThree/2)*.03436); 
Serial.print(centimeterLThree);

if(centimeterLThree > 0 && centimeterLThree < 15){ //conducts again like above except it is the 2nd hand placement
  sequenceFive = 100; 
  setFive = 1;
}
if(centimeterLThree > 15 && centimeterLThree < 30){
  sequenceFive = 300;
  setFive = 2;
}
if(centimeterLThree > 30 && centimeterLThree < 45){
  sequenceFive = 500;
  setFive = 3;
}
lcd.setCursor(0,1);
lcd.print(setFive); //displays the second hand placement
tone(times, sequenceFive); //plays the second tone
delay(2500);
noTone(times);

digitalWrite(trgPinFour, HIGH); //conducts again this time the third hand placement
delayMicroseconds(10);
digitalWrite(trgPinFour, LOW);
microsecondLFour = pulseIn(echPinFour, HIGH); 
centimeterLFour= ((microsecondLFour/2)*.03436); 
Serial.print(centimeterLFour);

if(centimeterLFour > 0 && centimeterLFour < 15){ //conducts again like above except it is the 3rd hand placement
  sequenceSix = 100;
  setFive = 1;
}
if(centimeterLFour > 15 && centimeterLFour < 30){
  sequenceSix = 300;
  setFive = 2;
}
if(centimeterLFour > 30 && centimeterLFour < 45){
  sequenceSix = 500;
  setFive = 3;
}
lcd.setCursor(0,1);
lcd.print(setFive); //displays the third hand placement
tone(times, sequenceSix); //plays the third tone
delay(2500);
noTone(times);

if(sequenceOne == sequenceFour && sequenceTwo == sequenceFive && sequenceThree == sequenceSix ){ //conducts if the set sequence is equal to the attempt of the passcode
  lcd.setCursor(0,1);
  lcd.print("Motor On");
  delay(2500);

while(servoCount == 0){ //conducts only once
    for(pos = 0; pos <= 180; pos = pos +1){ //turns the motor starting from 0 to 180 degrees
  myservo.write(pos);
  delay(15);
 }
 servoCount = servoCount +1; //increments so motor only spins once
  }
  myservo.write(pos);
  sup = 1; //sets that the motor has spun
}
else{ //conducts if the passcode does not match the set passcode
  lcd.setCursor(0,1);
  lcd.print("Try Again");
  delay(2500);
}

}
}

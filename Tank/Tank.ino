#include <IBusBM.h>

IBusBM IBus;
int ch1Read, ch2Read, ch3Read, ch4Read;


int enPinB = 2, enPinA = 7;
int IN1 = 6;
int IN2 = 5;
int IN3 = 4;
int IN4 = 3;


void setup() {
  // put your setup code here, to run once:
IBus.begin(Serial1);
Serial.begin(115200);

pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);

pinMode(enPinA,OUTPUT);
pinMode(enPinB,OUTPUT);
}

void loop() {
//reads channels and maps them to these global variables
ch1Read = readChannelMap(0);
ch2Read = readChannelMap(1);
ch3Read = readChannelMap(2);
ch4Read = readChannelMap(3);

//computes to which state to go depending on channel inputs 1 and 2
if(ch2Read>0 && ch1Read==0)// If right analog front center
{
  driveForward();
} 
else if(ch2Read<0 && ch1Read==0)// If right analog back center
{
  driveBackward();
}
else if(ch2Read == 0 && ch1Read < 0)// right analog right center
{
  driveTurnRight();//turns right in place
}
else if(ch2Read == 0 && ch1Read > 0)// right analog left center
{
  driveTurnLeft();//turns left in place
}
else if(ch2Read>0 && ch1Read < 0){
  driveForwardRight();
}
else if(ch2Read>0 && ch1Read > 0){
  driveForwardLeft();
}
else if(ch2Read<0 && ch1Read < 0){
  driveBackwardRight();
}
else if(ch2Read<0 && ch1Read > 0){
  driveBackwardLeft();
}
else {//If variable is zero
  driveStop();
}



// Serial.print("Ch1: ");
// Serial.print(ch1Read);
// Serial.print(" | ");
// Serial.print("Ch2: ");
// Serial.print(ch2Read);
// Serial.print("Ch3: ");
// Serial.print(ch3Read);
// Serial.print(" | ");
// Serial.print("Ch4: ");
// Serial.println(ch4Read);
}



//Reads a chanel and converts it to a value that is easier to compute with
int readChannelMap(int channelN)
{
  int channel = IBus.readChannel(channelN);
  int channelMap = 0;

      if(channel > 1550 || channel < 1450)
    {
        channelMap = map(channel,1000,2000,-100,100);
    } 
    else 
    {
        channelMap = 0;
    }
      return channelMap;
}

//This state makes the tank move fowards
void driveForward()
{
  int mapA = map(ch3Read,-100,100,0,255);
  analogWrite(enPinA,mapA);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);

  int mapB =  map(ch3Read,-100,100,0,255);
  analogWrite(enPinB,mapB);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);

  Serial.print(mapA);
  Serial.print(" ");
  Serial.println(mapB);
}

//This state makes the tank move backwards
void driveBackward()
{
  int mapA = map(ch3Read,-100,100,0,255);
  analogWrite(enPinA,mapA);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);

  int mapB =  map(ch3Read,-100,100,0,255);
  analogWrite(enPinB,mapB);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);

  Serial.print(mapA);
  Serial.print(" ");
  Serial.println(mapB);
}

//This state makes the tank stop moving
void driveStop(){
  analogWrite(enPinA,0);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);

  analogWrite(enPinB,0);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}

//This state makes the tank rotate to the left staying in place
void driveTurnLeft(){
  int mapA = map(ch3Read,-100,100,0,255);
  analogWrite(enPinA,mapA);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);

  int mapB =  map(ch3Read,-100,100,0,255);
  analogWrite(enPinB,mapB);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);

  Serial.print(mapA);
  Serial.print(" ");
  Serial.println(mapB);
}

//This state makes the tank rotate to the right staying in place
void driveTurnRight(){
  int mapA = map(ch3Read,-100,100,0,255);
  analogWrite(enPinA,mapA);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);

  int mapB =  map(ch3Read,-100,100,0,255);
  analogWrite(enPinB,mapB);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);

  Serial.print(mapA);
  Serial.print(" ");
  Serial.println(mapB);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//The states below multiply the side the tank should turn be a percentage to lower that side's speed causing the tank to turn.//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//This state makes the tank turn right while moving fowards
void driveForwardRight()
{
  int percentage = calculateMotorBias(ch1Read);
  int mapA = map(ch3Read,-100,100,0,255);
  analogWrite(enPinA,percentage * mapA);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);

  int mapB =  map(ch3Read,-100,100,0,255);
  analogWrite(enPinB,mapB);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);

  Serial.print(mapA * percentage);
  Serial.print(" ");
  Serial.println(mapB);
}

//This state makes the tank turn left while moving fowards
void driveForwardLeft()
{
  int percentage = calculateMotorBias(ch1Read);
  int mapA = map(ch3Read,-100,100,0,255);
  analogWrite(enPinA,mapA);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);

  int mapB =  map(ch3Read,-100,100,0,255);
  analogWrite(enPinB,mapB  * percentage);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);

  Serial.print(mapA * percentage);
  Serial.print(" ");
  Serial.println(mapB);
}

//This state makes the tank turn right while moving backwards
void driveBackwardRight()
{
  int percentage = calculateMotorBias(ch1Read);
  int mapA = map(ch3Read,-100,100,0,255);
  analogWrite(enPinA,mapA * percentage);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);

  int mapB =  map(ch3Read,-100,100,0,255);
  analogWrite(enPinB,mapB);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);

  Serial.print(mapA);
  Serial.print(" ");
  Serial.println(mapB);
}

//This state makes the tank turn left while moving backwards
void driveBackwardLeft()
{
  int percentage = calculateMotorBias(ch1Read);
  int mapA = map(ch3Read,-100,100,0,255);
  analogWrite(enPinA,mapA);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);

  int mapB =  map(ch3Read,-100,100,0,255);
  analogWrite(enPinB,mapB * percentage);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);

  Serial.print(mapA);
  Serial.print(" ");
  Serial.println(mapB);
}

//This function creates a percentage the the motor should be according to how far the user turns the analog left or right.
// If the analog is to the right 20% then the function will return 80%.
//ch will always be between -100 and 100 so dividing it by 100 will turn it into a percentage.
//subtracting 1 by that percentage will return what percentage the motor should be at.
int calculateMotorBias(int ch){
  int perc;
  if(ch > 0){
    perc = 1 - (ch/100);
  }
  else if (ch < 0){
    perc = 1 - ((-1*ch)/100);
  }
  return perc;
}
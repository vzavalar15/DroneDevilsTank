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
  // put your main code here, to run repeatedly:
ch1Read = readChannelMap(0);
ch2Read = readChannelMap(1);
ch3Read = readChannelMap(2);
ch4Read = readChannelMap(3);

if(ch2Read>0 && ch1Read==0)
{
  driveForward();
} 
else if(ch2Read<0 && ch1Read==0)
{
  driveBackward();
}
else if(ch2Read == 0 && ch1Read > 0){
  driveTurnRight();//turns left in place
}
else if(ch2Read == 0 && ch1Read < 0){
  driveTurnLeft();//turns in place
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

void driveStop(){
  analogWrite(enPinA,0);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);

  analogWrite(enPinB,0);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}

void driveTurnLeft(){
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

void driveTurnRight(){
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

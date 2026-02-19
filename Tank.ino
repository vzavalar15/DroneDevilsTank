#include <IBusBM.h>

IBusBM IBus;
int ch1, ch2, ch3, ch4;
int realVal1, realVal2, realVal3, realVal4;


void setup() {
  // put your setup code here, to run once:
IBus.begin(Serial1);
Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
ch1 = IBus.readChannel(0);
realVal1 = map(ch1,1000,2000,-100,100);

ch2 = IBus.readChannel(1);
realVal2 = map(ch2,1000,2000,-100,100);

ch3 = IBus.readChannel(2);
realVal3 = map(ch3,1000,2000,-100,100);

ch4 = IBus.readChannel(3);
realVal4 = map(ch4,1000,2000,-100,100);


Serial.print("Ch1: ");
Serial.print(realVal1);
Serial.print(" | ");
Serial.print("Ch2: ");
Serial.println(realVal2);
// Serial.print("Ch3: ");
// Serial.print(realVal3);
// Serial.print(" | ");
// Serial.print("Ch4: ");
// Serial.println(realVal4);

}

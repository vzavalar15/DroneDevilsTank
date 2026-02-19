#include <IBusBM.h>

IBusBM IBus;
int ch3, ch4;
int realVal3, realVal4;


void setup() {
  // put your setup code here, to run once:
IBus.begin(Serial1);
Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
ch3 = IBus.readChannel(2);
realVal3 = map(ch3,1000,2000,-100,100);

ch4 = IBus.readChannel(3);
realVal4 = map(ch4,1000,2000,-100,100);

Serial.print("Ch3: ");
Serial.print(realVal3);
Serial.print(" | ");
Serial.print("Ch4: ");
Serial.println(realVal4);

}

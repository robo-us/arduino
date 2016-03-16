#include <SoftwareSerial.h>  // TX RX software library for bluetooth

SoftwareSerial BT(10, 11); //TX, RX respetively
String readdata;

void setup() {
 BT.begin(9600);
 Serial.begin(9600);
  pinMode(3, OUTPUT); // connect to input 1 of l293d
  pinMode(4, OUTPUT); // connect to input 4 of l293d
  pinMode(5, OUTPUT); // connect to input 3 of l293d
  pinMode(6, OUTPUT); // connect to input 2 of l293d

}
//-----------------------------------------------------------------------// 
void loop() {
  while (BT.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable
  char c = BT.read(); //Conduct a serial read
  readdata += c; //build the string- "forward", "reverse", "left" and "right"
  } 
  if (readdata.length() > 0) {
    Serial.println(readdata); // print data to serial monitor
// if data received as forward move robot forward
  if(readdata == "forward") 
  {
    digitalWrite(3, HIGH);
    digitalWrite (4, HIGH);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    delay(100);
  }
  // if data received as reverse move robot reverse

  else if(readdata == "reverse")
  {
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(6,HIGH);
    delay(100);
  }
// if data received as right turn robot to right direction.
  else if (readdata == "right")
  {
    digitalWrite (3,HIGH);
    digitalWrite (4,LOW);
    digitalWrite (5,LOW);
    digitalWrite (6,LOW);
    delay (100);
   
  }
// if data received as left turn robot to left direction
 else if ( readdata == "left")
 {
   digitalWrite (3, LOW);
   digitalWrite (4, HIGH);
   digitalWrite (5, LOW);
   digitalWrite (6, LOW);
   delay (100);
 }
 // if data received as stop, halt the robot

 else if (readdata == "stop")
 {
   digitalWrite (3, LOW);
   digitalWrite (4, LOW);
   digitalWrite (5, LOW);
   digitalWrite (6, LOW);
   delay (100);
 }

readdata="";}} //Reset the variable

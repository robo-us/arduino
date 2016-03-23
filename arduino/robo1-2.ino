#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11); //TX, RX
String state;// łańcuch do przechowywania poleceń z bluetooth


void setup() {
 BT.begin(9600);// w bluetooth komunikacja szeregowa będzie się odbywać na pinach 10 i 11
 Serial.begin(9600); // rozpoczęcie komunikacji szeregowej
  pinMode(13, OUTPUT); // podłączenie LEd'a  do 13 portu
}

//----------------------------------------------------------------------//
void loop() {
  while (BT.available()){  // wykonuje dopóki odczytuje bity
  delay(10); // opóźnienie aby zachować stabilność
  char c = BT.read(); // odczytanie z bluetootha
  state += c; // zbudowanie łańcucha innego niż "On" lub "off"
  }  
  if (state.length() > 0) {
    Serial.println(state); 

    if(state == "on") 
    {
      digitalWrite(13, HIGH);
    }
  
    else if(state == "off") 
    {
      digitalWrite(13, LOW);
     }
  
  state =""; // resetowanie zmiennej
  }
 } 


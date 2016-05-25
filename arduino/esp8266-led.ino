#include <SoftwareSerial.h>  //dolaczenie biblioteki do obsługi programowego interfejsu UART
         
SoftwareSerial esp01(2,3); // Inicjalizacja programowego interfejsu UART: 2-RX (polaczyc z Tx modulu ESP); 3-TX (polaczyc z Rx modulu ESP)
     
void setup()
{
  Serial.begin(9600); // Inicjalizacja sprzetowego interfejsu UART z prędkościa 9600 bps - do komunikacji z komputerem poprzez USB
      esp01.begin(9600); // Inicjalizacja programowego  interfejsu UART z prędkościa 9600 bps - do komunikacji z modulem ESP
       
  pinMode(11,OUTPUT);    //ustawienie pinu 11 jako wejście dla diody LED nr 1
  digitalWrite(11,LOW);  //podanie stanu niskiego na pin 11 - dioda 1 domyślnie wyłączone
       
  pinMode(12,OUTPUT);    //ustawienie pinu 12 jako wejście dla diody LED nr 2
  digitalWrite(12,LOW);  //podanie stanu niskiego na pin 12 - dioda 2 domyślnie wyłączone
       
  pinMode(13,OUTPUT);    //ustawienie pinu 13 jako wejście dla diody LED nr 3
  digitalWrite(13,LOW);  //podanie stanu niskiego na pin 13 - dioda 3 domyślnie wyłączone
        
  //Wysyłanie komend incjalizacyjnych dla modulu ESP
  sendData("AT+RSTrn",2000);              //reset modułu
  sendData("AT+CWMODE=2rn",1000);         //ustawienie w trybie Access Point
  sendData("AT+CIFSRrn",1000);            //uzyskanie adresu IP (domyślnie 192.168.4.1)
  sendData("AT+CIPMUX=1rn",1000);         //włączenie trybu połączeń wielokrotnych
  sendData("AT+CIPSERVER=1,80rn",1000);   //ustawienie serwera na porcie 80
}
      
void loop()
{
  if(esp01.available()) // sprawdzenie czy moduł otrzymał dane
  {
    if(esp01.find("+IPD,"))
    {
     delay(1000); // czekanie na zapełnienie bufora danymi
          
     // odczytanie ID połączenia
     int connectionId = esp01.read()-48; //odczytanie wartosci ASCI: odjęto 48 ponieważ funkcja read() zwraca wartość dziesiętną ASCII na pozycji 48
          
     esp01.find("pin="); // wyszukanie frazy "pin=" oraz ustawienie tam "kursora"
          
     int pinNumber = (esp01.read()-48)*10; // pobranie pierwszej cyfry, np. dla pinu 13, pierwsza cyfra to 1, należy ją pomnożyć przez 10
     pinNumber += (esp01.read()-48);       //pobranie drugiej cyfry, np. dla pinu 13, druga cyfra to 3, należy ją dodać do poprzedniego wyniku
          
     digitalWrite(pinNumber, !digitalRead(pinNumber)); // zmiana stanu wybranego pinu    
          
     // zamknięcie połączenia
     String closeCommand = "AT+CIPCLOSE=";
     closeCommand+=connectionId;     // ID połączenia odczytane na początku
     closeCommand+="rn";
          
     sendData(closeCommand,1000); // wyslanie komend zakoczenia polaczenia
    }
  }
}
      
/*
* Funkcja wysyłająca komendy do modułu ESP01
* Parametry:
* command - komenda do wysłania
* timeout - czas oczekiwania na odpowiedź
*/
String sendData(String command, const int timeout)
{
    String response = "";
         
    esp01.print(command); // wysłanie polecenia do ESP01
         
    long int time = millis();
         
    while( (time+timeout) > millis())
    {
      while(esp01.available()) //jeśli są jakieś dane z modułu, wtedy następuje ich odczyt
      {
        char c = esp01.read(); // odczyt kolejnego znaku
        response += c;
      }
    }
    Serial.print(response);
    return response;
}

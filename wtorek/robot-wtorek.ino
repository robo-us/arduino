/*Ustawienia dla PWM
 * int E1 = 5; //E1
int M1 = 4; //M1
int E2 = 6; //E2
int M2 = 7; //M2
*/
/*Ustawienia dla PLL*/
int E1 = 4;
int M1 = 5;
int E2 = 7;
int M2 = 6;

int Trig = 12;    //pin 12 Arduino połączony z pinem Trigger czujnika
int Echo = 11;    //pin 11 Arduino połączony z pinem Echo czujnika
int CM;           //odległość w cm
long CZAS;        //długość powrotnego impulsu w uS
int button = 2;   //pin 2 Arduino połaczony z przyciskiem
int redLed = 3;   //pin 3 Arduino polaczony z czerwoną diodą LED - jazda do tyłu
int greenLed = 8; //pin 8 Arduino połączony z zieloną diodą LED - jazda do przodu

int buttonState = LOW;
long lastDebaunceTime = 0;
long debaunceDelay = 50;

void setup()
{
  Serial.begin(9600);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(button, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(Trig, OUTPUT);                     //ustawienie pinu 12 w Arduino jako wyjście
  pinMode(Echo, INPUT);                      //ustawienie pinu 11 w Arduino jako wejście
  digitalWrite(button, LOW);
}

void loop()
{
  while (!buttonPressed()) {
    Serial.println(buttonState);
    Serial.println("przycik nie wcisniety");
  }
  Serial.println("przycisk wcisniety");
  if (pomiar_odleglosci()> 30) {
    forward(150);
    Serial.println("wyszedlem z forward");
    delay(200);
    Serial.println(pomiar_odleglosci());
  } else {
    stopMotors();
  }
  //delay(2000);
}

void forward(int value) {
  Serial.println("jestem w forward");
  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, LOW);
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, value);
  analogWrite(E2, value);
}

void backward(int value, int distance) {
  digitalWrite(greenLed, LOW);
  digitalWrite(redLed, HIGH);
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  analogWrite(E1, value);
  analogWrite(E2, value);
  delay(distance);
}

void turnLeft(int value, int distance) {
  digitalWrite(M1, HIGH);
  //  digitalWrite(M2, HIGH);
  analogWrite(E1, value);
  //  analogWrite(E2, value);
  delay(distance);
}

void turnRight(int value, int distance) {
  //  digitalWrite(M1,HIGH);
  digitalWrite(M2, HIGH);
  //  analogWrite(E1, value);
  analogWrite(E2, value);
  delay(distance);
}

void stopMotors() {
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  analogWrite(E1, 0);
  analogWrite(E2, 0);
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
}

boolean buttonPressed() {

  buttonState = digitalRead(button);
  
  if ((millis() - lastDebaunceTime) > debaunceDelay) {
    if (buttonState == HIGH) {
      lastDebaunceTime = millis();
      digitalWrite(button, HIGH);
      buttonState = HIGH;
      return true;
    }
    else if (buttonState == LOW) {
      lastDebaunceTime = millis();
      digitalWrite(button, LOW);
      buttonState = LOW;
      stopMotors();
      return false;
    }
  }
}

int pomiar_odleglosci(){
  digitalWrite(Trig, LOW);        //ustawienie stanu wysokiego na 2 uS - impuls inicjalizujacy - patrz dokumentacja
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);       //ustawienie stanu wysokiego na 10 uS - impuls inicjalizujacy - patrz dokumentacja
  delayMicroseconds(15);
  digitalWrite(Trig, LOW);
  digitalWrite(Echo, HIGH); 
  CZAS = pulseIn(Echo, HIGH);
  CM = CZAS / 58;                //szerokość odbitego impulsu w uS podzielone przez 58 to odleglosc w cm - patrz dokumentacja
  return CM; 
}

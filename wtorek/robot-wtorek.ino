int E1 = 5; //E1
int M1 = 4; //M1
int E2 = 6; //E2
int M2 = 7; //M2
int button = 2;
int redLed = 3;
int greenLed = 4;

void setup()
{
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(button, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  digitalWrite(button, LOW);
}

void loop()
{
  //pętla while służy jako pauza w wykonywaniu programu
  //doóki nie wciśniemy przycisku nic się nie wykona
  while (!buttonPressed()) {
  }
  forward(100, 1000);
  backward(100, 1000);
  stopMotors();
}

void forward(int value, int distance) {
  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, LOW);
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, value);
  analogWrite(E2, value);
  delay(distance);
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
  analogWrite(E1, 0);
  analogWrite(E2, 0);
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
}

boolean buttonPressed() {
  if (digitalRead(button) == HIGH) {
    delay(2000);
    return true;
  } else {
    return false;
  }
}

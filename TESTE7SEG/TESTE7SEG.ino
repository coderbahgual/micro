int pinA = 3;
int pinB = 2;
int pinC = 7;
int pinD = 8;
int pinE = 9;
int pinF = 4;
int pinG = 5;
int pinDP = 6;

boolean high =false;

void setup()
{
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinDP, OUTPUT);
}

void loop()
{
  num8();
  blinkDP();
  reset();
  blinkDP();
}

void blinkDP() // Faz o DP piscar.
{
    if (high)
  {
    digitalWrite(pinDP, HIGH);
  }
  else
  {
    digitalWrite(pinDP, LOW);
  }
  
  high = !high;
  delay(1000);
}

void reset()
{
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
  digitalWrite(pinDP,HIGH);
}

void num8() // Número 8.
{
  digitalWrite(pinA, LOW);
//  digitalWrite(pinB, LOW);
//  digitalWrite(pinC, LOW);
//  digitalWrite(pinD, LOW);
//  digitalWrite(pinE, LOW);
//  digitalWrite(pinF, LOW);
//  digitalWrite(pinG, LOW);
}

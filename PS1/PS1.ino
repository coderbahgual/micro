int pinA = 3;
int pinB = 2;
int pinC = 7;
int pinD = 8;
int pinE = 9;
int pinF = 4;
int pinG = 5;
int pinP = 6;

int posicao = 0;
int pinINT0 = 21; // atm2560 pin INT0
int pinINT1 = 20; // atm2560 pin INT1

void setup() {
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinP, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pinINT0), anterior, RISING);
  attachInterrupt(digitalPinToInterrupt(pinINT1), proximo, RISING);
}

void loop() {
//int hello_at328p[12] = { H,  E,  L,  L, O,  _,  A, T, 3, 2, 8,  P};
  int hello_at328p[12] = {12, 11, 13, 13, 0, 16, 10, 7, 3, 2, 8, 14};
  reset();
  if (posicao > 12) posicao = 0;
  numeros(hello_at328p[posicao]);
  posicao++; // ++posicao;
  delay(2000);
}

void anterior() {
  if (posicao == 0) {
    posicao = 12;
  } else {
    --posicao;
  }
  digitalWrite(pinP, LOW);
  delay(5000);
  digitalWrite(pinP, HIGH);
}

void proximo() {
  if (posicao == 12) {
    posicao = 0;
  } else {
    ++posicao;
  }
  digitalWrite(pinP, LOW);
  delay(5000);
  digitalWrite(pinP, HIGH);
}

void reset() {
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
  digitalWrite(pinP, HIGH);
}

void numeros(int i) {
    reset();
    switch(i) {
      case 0: // zero e O
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, LOW);
        digitalWrite(pinC, LOW);
        digitalWrite(pinD, LOW);
        digitalWrite(pinE, LOW);
        digitalWrite(pinF, LOW);
      break;
      case 1:
        digitalWrite(pinB, LOW);
        digitalWrite(pinC, LOW);
      break;
      case 2:
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, LOW);
        digitalWrite(pinG, LOW);
        digitalWrite(pinE, LOW);
        digitalWrite(pinD, LOW);
      break;
      case 3:
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, LOW);
        digitalWrite(pinG, LOW);
        digitalWrite(pinC, LOW);
        digitalWrite(pinD, LOW);
      break;
      case 4:
        digitalWrite(pinF, LOW);
        digitalWrite(pinG, LOW);
        digitalWrite(pinB, LOW);
        digitalWrite(pinC, LOW);
      break;
      case 5:
        digitalWrite(pinA, LOW);
        digitalWrite(pinF, LOW);
        digitalWrite(pinG, LOW);
        digitalWrite(pinC, LOW);
        digitalWrite(pinD, LOW);
      break;
      case 6:
        digitalWrite(pinF, LOW);
        digitalWrite(pinE, LOW);
        digitalWrite(pinD, LOW);
        digitalWrite(pinC, LOW);
        digitalWrite(pinG, LOW);
      break;
      case 7: // sete e T
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, LOW);
        digitalWrite(pinC, LOW);
      break;
      case 8:
        digitalWrite(pinA, LOW);
        digitalWrite(pinF, LOW);
        digitalWrite(pinG, LOW);
        digitalWrite(pinC, LOW);
        digitalWrite(pinD, LOW);
        digitalWrite(pinE, LOW);
        digitalWrite(pinB, LOW);
      break;
      case 9:
        digitalWrite(pinG, LOW);
        digitalWrite(pinF, LOW);
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, LOW);
        digitalWrite(pinC, LOW);
      break;
      case 10: // A
        digitalWrite(pinE, LOW);
        digitalWrite(pinF, LOW);
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, LOW);
        digitalWrite(pinC, LOW);
        digitalWrite(pinG, LOW);
      break;
      case 11: // E
        digitalWrite(pinA, LOW);
        digitalWrite(pinF, LOW);
        digitalWrite(pinE, LOW);
        digitalWrite(pinD, LOW);
        digitalWrite(pinG, LOW);
      break;
      case 12: // H
        digitalWrite(pinF, LOW);
        digitalWrite(pinE, LOW);
        digitalWrite(pinB, LOW);
        digitalWrite(pinC, LOW);
        digitalWrite(pinG, LOW);
      break;
      case 13: // L
        digitalWrite(pinF, LOW);
        digitalWrite(pinE, LOW);
        digitalWrite(pinD, LOW);
      break;
      case 14: // P
        digitalWrite(pinE, LOW);
        digitalWrite(pinF, LOW);
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, LOW);
        digitalWrite(pinG, LOW);
      break;
      case 15: // T2
        digitalWrite(pinE, LOW);
        digitalWrite(pinF, LOW);
        digitalWrite(pinA, LOW);
      break;
      case 16: // _
        digitalWrite(pinD, LOW);
      break;
    }
}

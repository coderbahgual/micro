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

//int hello_at328p[12] = { H,  E,  L, L., O,  _,  A, T, 3, 2, 8,  P};
  int hello_at328p[12] = {12, 11, 13, 17, 0, 16, 10, 7, 3, 2, 8, 14};

void setup() {
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinP, OUTPUT);
  pinMode(pinINT0, INPUT);
  pinMode(pinINT1, INPUT);
  attachInterrupt(digitalPinToInterrupt(pinINT0), anterior, RISING);
  attachInterrupt(digitalPinToInterrupt(pinINT1), proximo, RISING);

  // Configuração do timer1 
  TCCR1A = 0; //confira timer para operação normal pinos OC1A e OC1B desconectados
  TCCR1B = 4; //limpa registrador
  TIMSK1 |= (1 << TOIE1); // habilita a interrupção do TIMER1
  //---------------SEM PRESCALER--------------------------------------
   // TCCR1B = 1;  // modo normal sem prescaler
   TCNT1 = 0; // 1s == 0xC2F7
  //SEM PRESCALER
  // 65536 ciclos * 6.25e-08 (periodo do ciclo em s) =  0.004096 s = 4.09ms tempo para interrupcao
  // 10000 ms / 4.09 ms/interrupcao = +-245 
  // 245 ciclos teremos 1S  
}

void loop() {
  numeros(hello_at328p[posicao]);
}

ISR(TIMER1_OVF_vect) {
  // reset();
  if (posicao == 11) {
    posicao = 0;
  } else {
    posicao++; // ++posicao;
  }
  // delay(2000);
}

void anterior() {
  if (posicao == 0) {
    posicao = 11;
  } else {
    posicao--; // --posicao;
  }
  digitalWrite(pinP, LOW);
  delay(5000);
  digitalWrite(pinP, HIGH);
}

void proximo() {
  if (posicao == 11) {
    posicao = 0;
  } else {
    posicao++; // ++posicao;
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
      case 17: // L.
        digitalWrite(pinF, LOW);
        digitalWrite(pinE, LOW);
        digitalWrite(pinD, LOW);
        digitalWrite(pinP, LOW);
      break;
    }
}

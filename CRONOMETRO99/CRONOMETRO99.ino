//int pinUnidade[8] = {B, A, F, G, P, C, D, E}; // DISPLAY UNIDADE
  int pinUnidade[8] = {2, 3, 4, 5, 6, 7, 8, 9};
//int pinDezena[8] = { B,  A,  F,  G,  P,  C,  D,  E}; // DISPLAY DEZENA
  int pinDezena[8] = {22, 24, 26, 28, 30, 32, 34, 36};

int posicaoUni = 0;
int posicaoDez = 0;

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(pinUnidade[i], OUTPUT);
    pinMode(pinDezena[i], OUTPUT);
  }

  // Configuração do timer1
  TCCR1A = 0;                       //confira timer para operação normal pinos OC1A e OC1B desconectados
  TCCR1B = 0;                       //limpa registrador
  TCCR1B |= (1<<CS10)|(1 << CS12);  // configura prescaler para 1024: CS12 = 1 e CS10 = 1
  TCNT1 = 0xC2F7;                   // incia timer com valor para que estouro ocorra em 1 segundo
                                    // 65536-(16MHz/1024/1Hz) = 49911 = 0xC2F7
  TIMSK1 |= (1 << TOIE1);           // habilita a interrupção do TIMER1

  // Configuração do timer2
  TCCR2A = 0; // timer operando em modo normal, registrador de controle do timer2 (8 bits em zero)
  TCCR2B = 7; //prescaler 1:1024, divisor permite contar tempos maiores com o timer (3 bits menos significativos) multiplica o ciclo de maquina por 1024
  TCNT2 = 0;  //registrador de contagem
  TIMSK2 = 1; //habilita interrupçao do timer2
/*
 overflow = timer2_cont * prescaler * ciclo de maquina
 ciclo de maquina = 16mhz = 1/16000000 = 62,5ns
 overflow = 256 * 1024 * 62,5E-9 =  16,38ms
 A cada 16,5ms ocorre um interrupçao do timer2
*/
}

void loop() {
}

ISR(TIMER1_OVF_vect) {
  TCNT1 = 0xC2F7; // Renicia TIMER
  if (posicaoUni == 9 && posicaoDez == 9) {
    posicaoUni = 0;
    posicaoDez = 0;
  } else if (posicaoUni != 9) {
    posicaoUni++;
  } else {
    posicaoUni = 0;
    posicaoDez++;
  }
}

ISR(TIMER2_OVF_vect) {
  TCNT2 = 0; // reinicializa registrador de contagem do timer2 (8 bits)
  numeros(posicaoUni, pinUnidade);
  numeros(posicaoDez, pinDezena);
}

void reset(int *pin) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(pin[i], HIGH);
  }
}

void numeros(int i, int *pin) {
    reset(pin);
    // {B, A, F, G, P, C, D, E};
    // {0, 1, 2, 3, 4, 5, 6, 7};
    switch(i) {
      case 0: // zero e O
        digitalWrite(pin[1], LOW);
        digitalWrite(pin[0], LOW);
        digitalWrite(pin[5], LOW);
        digitalWrite(pin[6], LOW);
        digitalWrite(pin[7], LOW);
        digitalWrite(pin[2], LOW);
      break;
      case 1:
        digitalWrite(pin[0], LOW);
        digitalWrite(pin[5], LOW);
      break;
      case 2:
        digitalWrite(pin[1], LOW);
        digitalWrite(pin[0], LOW);
        digitalWrite(pin[3], LOW);
        digitalWrite(pin[7], LOW);
        digitalWrite(pin[6], LOW);
      break;
      case 3:
        digitalWrite(pin[1], LOW);
        digitalWrite(pin[0], LOW);
        digitalWrite(pin[3], LOW);
        digitalWrite(pin[5], LOW);
        digitalWrite(pin[6], LOW);
      break;
      case 4:
        digitalWrite(pin[2], LOW);
        digitalWrite(pin[3], LOW);
        digitalWrite(pin[0], LOW);
        digitalWrite(pin[5], LOW);
      break;
      case 5:
        digitalWrite(pin[1], LOW);
        digitalWrite(pin[2], LOW);
        digitalWrite(pin[3], LOW);
        digitalWrite(pin[5], LOW);
        digitalWrite(pin[6], LOW);
      break;
      case 6:
        digitalWrite(pin[2], LOW);
        digitalWrite(pin[7], LOW);
        digitalWrite(pin[6], LOW);
        digitalWrite(pin[5], LOW);
        digitalWrite(pin[3], LOW);
      break;
      case 7: // sete e T
        digitalWrite(pin[1], LOW);
        digitalWrite(pin[0], LOW);
        digitalWrite(pin[5], LOW);
      break;
      case 8:
        digitalWrite(pin[1], LOW);
        digitalWrite(pin[2], LOW);
        digitalWrite(pin[3], LOW);
        digitalWrite(pin[5], LOW);
        digitalWrite(pin[6], LOW);
        digitalWrite(pin[7], LOW);
        digitalWrite(pin[0], LOW);
      break;
      case 9:
        digitalWrite(pin[3], LOW);
        digitalWrite(pin[2], LOW);
        digitalWrite(pin[1], LOW);
        digitalWrite(pin[0], LOW);
        digitalWrite(pin[5], LOW);
      break;
      case 10: // A
        digitalWrite(pin[7], LOW);
        digitalWrite(pin[2], LOW);
        digitalWrite(pin[1], LOW);
        digitalWrite(pin[0], LOW);
        digitalWrite(pin[5], LOW);
        digitalWrite(pin[3], LOW);
      break;
      case 11: // E
        digitalWrite(pin[1], LOW);
        digitalWrite(pin[2], LOW);
        digitalWrite(pin[7], LOW);
        digitalWrite(pin[6], LOW);
        digitalWrite(pin[3], LOW);
      break;
      case 12: // H
        digitalWrite(pin[2], LOW);
        digitalWrite(pin[7], LOW);
        digitalWrite(pin[0], LOW);
        digitalWrite(pin[5], LOW);
        digitalWrite(pin[3], LOW);
      break;
      case 13: // L
        digitalWrite(pin[2], LOW);
        digitalWrite(pin[7], LOW);
        digitalWrite(pin[6], LOW);
      break;
      case 14: // P
        digitalWrite(pin[7], LOW);
        digitalWrite(pin[2], LOW);
        digitalWrite(pin[1], LOW);
        digitalWrite(pin[0], LOW);
        digitalWrite(pin[3], LOW);
      break;
      case 15: // T2
        digitalWrite(pin[7], LOW);
        digitalWrite(pin[2], LOW);
        digitalWrite(pin[1], LOW);
      break;
      case 16: // _
        digitalWrite(pin[6], LOW);
      break;
      case 17: // L.
        digitalWrite(pin[2], LOW);
        digitalWrite(pin[7], LOW);
        digitalWrite(pin[6], LOW);
        digitalWrite(pin[4], LOW);
      break;
      case 18: // -
        digitalWrite(pin[3], LOW);
      break;
      case 19: // .
        digitalWrite(pin[4], LOW);
      break;
    }
}

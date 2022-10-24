/*
Modifique sua implementação da sinaleira que já utilizava interrupções externas para realizar as trocas dos LEDS através de
interrupções com TIMERS (Overflow ou CTC), com o TIMER de sua escolha (0 ou 1 ou 2);
O tempo de troca e quais TIMERS serão utilizados serão critérios do aluno assim como a política de mudança (1 TIMER para cada
led ou todos os leds no mesmo TIMER);
*/

// #include "src/PinChangeInterrupt.h"
// #include "PinChangeInt.h"

int ledVermelho = 8;
int ledAmarelo = 9;
int ledVerde = 10;
int ledAzul = 13; // protecao
// int pinInt = 21; // atm2560 pin INT0
int pinInt = 2; // atm2560 pin INT4

int counter = 0;
int qtd_seg = 0;

void interrupcao() {
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAzul, HIGH);
    delay(100000);
    digitalWrite(ledAzul, LOW);
    delay(1000);
}

// the setup function runs once when you press reset or power the board
void setup() { 
  pinMode(pinInt, INPUT_PULLUP);
  
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pinInt), interrupcao, RISING);

  // attachPCINT(digitalPinToPCINT(pinInt), interrupcao, CHANGE);
  // attachPinChangeInterrupt(digitalPinToPCINT(pinInt), interrupcao, RISING);
  
  // attachPinChangeInterrupt(pinInt, interrupcao, CHANGE);

  // Configuração do timer1 
  TCCR1A = 0; //confira timer para operação normal pinos OC1A e OC1B desconectados
  TCCR1B = 0; //limpa registrador
  TIMSK1 |= (1 << TOIE1); // habilita a interrupção do TIMER1
  TCCR1B = 1; // modo normal sem prescaler
  TCNT1 = 0; //SEM PRESCALER
  // 65536 ciclos * 6.25e-08 (periodo do ciclo em s) =  0.004096 s = 4.09ms tempo para interrupcao
  // 10000 ms / 4.09 ms/interrupcao = +-245 
  // 245 ciclos teremos 1S  
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(ledVermelho, LOW);
  // digitalWrite(ledVerde, HIGH);
  delay(2000);
  // digitalWrite(ledVerde, HIGH);
  digitalWrite(ledAmarelo, HIGH);
  delay(1000);
  // digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVermelho, HIGH);
  delay(3000);
}

ISR(TIMER1_OVF_vect) { //interrupção do TIMER1 
  // SEM PRESCALER
  if (counter == 245) {
    counter = 0 ;
    qtd_seg++;
    if (qtd_seg == 2) {
      qtd_seg = 0;
      digitalWrite(ledVerde, digitalRead(ledVerde) ^ 1); // inverte estado do led
    }
  }
  TCNT1 = 0;
  counter++;

}

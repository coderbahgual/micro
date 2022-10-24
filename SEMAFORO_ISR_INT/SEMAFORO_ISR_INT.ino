/*
Utilize a solução anterior de PISCA LED2, e introduza uma função que trata interrupções externas (int0/int1) criadas por um pushbutton;
A rotina de interrupção deverá desligar os três LEDs do semáforo e o mesmo tempo ligar um quarto LED de proteção.
Utilize a função attachedinterrupt do arduino, para a implementação da interrupção;
*/

int ledVermelho = 8;
int ledAmarelo = 9;
int ledVerde = 10;
int ledAzul = 13; // protecao
// int pinInt = 21; // atm2560 pin INT0
int pinInt = 2; // atm2560 pin INT4

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
  pinMode(pinInt, INPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pinInt), interrupcao, RISING);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledVerde, HIGH);
  delay(2000);
  digitalWrite(ledVerde, HIGH);
  digitalWrite(ledAmarelo, HIGH);
  delay(1000);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVermelho, HIGH);
  delay(3000);
}

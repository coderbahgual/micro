/*
Agora crie o seu próprio código de piscaLED, porém, utilize três LEDs para criar uma implementação de semáforo;
Considere os tempos para as transições;
Verde -> Verde/Amarelo -> Vermelho
Vermelho -> Verde
Obs: Não esqueça de utilizar resistores com o LED
*/

int ledVermelho = 8;
int ledAmarelo = 9;
int ledVerde = 10;

// the setup function runs once when you press reset or power the board
void setup() { 
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledVerde, HIGH);
  delay(4000); 
  digitalWrite(ledAmarelo, HIGH);
  delay(2000);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVermelho, HIGH);
  delay(4000);
}

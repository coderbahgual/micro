int ledVermelho = 8;
int ledAmarelo = 9;
int brilhoVermelho = 0;
int brilhoAmarelo = 255;
int fadeVermelho = 5;
int fadeAmarelo = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(ledVermelho, brilhoVermelho);
  analogWrite(ledAmarelo, brilhoAmarelo);

  brilhoVermelho = brilhoVermelho + fadeVermelho;
  brilhoAmarelo = brilhoAmarelo - fadeAmarelo;

  if (brilhoVermelho <= 0 || brilhoVermelho >= 255) { // reverte o efeito
    fadeVermelho = -fadeVermelho;
  }

  if (brilhoAmarelo <= 0 || brilhoAmarelo >= 255) { // reverte o efeito
    fadeAmarelo = -fadeAmarelo;
  }

  delay(30); // 50 ms para ver efeito
}

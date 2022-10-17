int ledVermelho = 8;
int ledAmarelo = 9;
int brilhoVermelho = 0;
int brilhoAmarelo = 255;
int fade = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(ledVermelho, brilhoVermelho);
  analogWrite(ledAmarelo, brilhoAmarelo);

  brilhoVermelho = brilhoVermelho + fade;
  brilhoAmarelo = brilhoAmarelo - fade;

  if (brilhoVermelho <= 0 || brilhoVermelho >= 255) { // reverte o efeito
    fade = -fade;
  }

  delay(50); // 50 ms para ver efeito
}

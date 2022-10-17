int ledVermelho = 8;
int ledAmarelo = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledVermelho, HIGH);
  digitalWrite(ledAmarelo, LOW);
  delay(500);
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledAmarelo, HIGH);
  delay(500);
}

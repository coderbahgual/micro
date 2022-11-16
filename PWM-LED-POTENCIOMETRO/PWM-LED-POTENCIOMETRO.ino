// 
int ledPin = 9;     // LED conectado ao pino digital 9
int analogPin = 3;  // potenciômetro conectado ao pino analógico 3
int val = 0;        // variável para guradar o valor lido

void setup() {
  pinMode(ledPin, OUTPUT);  // configura  o pino como saída
}

void loop() {
  val = analogRead(analogPin);  // lê o pino de entrada analógica
  analogWrite(ledPin, val / 4); // analogRead retorna valores de 0 a 1023, 
                                // analogWrite recebe de 0 a 255
}

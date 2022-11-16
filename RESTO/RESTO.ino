char receivedChar;
int resto = 0;
int divisor = 3;

void setup() {
  Serial.begin(9600);
  Serial.println("<Arduino>");
}

void loop() {
  if (Serial.available() > 0) {
    receivedChar = Serial.read();
    if (isDigit(receivedChar)) { // isDigit() verifica se um caracter eh um numero
          restoDivisao();
        }
    }
}

void restoDivisao() {
  resto = receivedChar % divisor; // % -> resto da divisao
  Serial.println(resto);
}

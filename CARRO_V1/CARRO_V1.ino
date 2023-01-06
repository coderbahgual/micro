// Define os pinos de utilização do Driver L298.
const int motorLF  = 11;    // Pin  5 of L293.
const int motorLB  = 10;    // Pin  6 of L293.
const int motorDB  = 9;   // Pin 10 of L293.
const int motorDF  = 8;   // Pin 9 of L293.

const int buzzer = 12;   // Define o Pino 13 como pino do Buzzer.

// Variáveis Úteis
int i = 0;
int j = 0;
int state_rec;
int vSpeed = 200;   // Define velocidade padrão 0 < x < 255.
char state;



void setup() {
  // Inicializa as portas como entrada e saída.
  pinMode(motorLF, OUTPUT);
  pinMode(motorLB, OUTPUT);
  pinMode(motorDB, OUTPUT);
  pinMode(motorDF, OUTPUT);
  pinMode(buzzer, OUTPUT);
//  pinMode(BTState, INPUT);

  // Inicializa a comunicação serial em 9600 bits.
  Serial.begin(9600);
  Serial.println("Motor test!");
}

void loop() {
  // Para o carro quando a conexão com Bluetooth é perdida ou desconectada.
//  if (digitalRead(BTState) == LOW) {
    state = 'F';
//  }

  // Salva os valores da variável 'state'
//  if (Serial.available() > 0) {
//    state_rec = Serial.read();
//    state = state_rec;//.trim();
//    Serial.println(vSpeed);
//  }

  // Altera a velocidade de acordo com valores especificados.
  if (state == '0') {
    vSpeed = 0;
  }
  else if (state == '4') {
    vSpeed = 100;
  }
  else if (state == '6') {
    vSpeed = 155;
  }
  else if (state == '7') {
    vSpeed = 180;
  }
  else if (state == '8') {
    vSpeed = 200;
  }
  else if (state == '9') {
    vSpeed = 230;
  }
  else if (state == 'q') {
    vSpeed = 255;
  }

  if (state != 'S') {
    Serial.print(state);
  }

  // Se o estado recebido for igual a 'F', o carro se movimenta para frente.
  if (state == 'F') {
    analogWrite(motorDB, 0);
    analogWrite(motorLF, vSpeed);
    analogWrite(motorLB, 0);
    analogWrite(motorDF, vSpeed);
  }

    else if (state == 'I') {  // Se o estado recebido for igual a 'I', o carro se movimenta para Frente Esquerda.
    analogWrite(motorLF, vSpeed); 
    analogWrite(motorLB, 0);
    analogWrite(motorDB, 100);    
    analogWrite(motorDF, 0);
  }

    else if (state == 'G') {   // Se o estado recebido for igual a 'G', o carro se movimenta para Frente Direita.
    analogWrite(motorLF, 100); 
    analogWrite(motorLB, 0);
    analogWrite(motorDB, vSpeed);      
    analogWrite(motorDF, 0);
  }

  else if (state == 'B') { // Se o estado recebido for igual a 'B', o carro se movimenta para trás.
    analogWrite(motorLF, 0);
    analogWrite(motorDB, 0);
    analogWrite(motorDF, vSpeed);
    analogWrite(motorLB, vSpeed);
  }

   else if (state == 'H') {  // Se o estado recebido for igual a 'H', o carro se movimenta para Trás Esquerda.
    analogWrite(motorLF, 0);   
    analogWrite(motorLB, vSpeed);
    analogWrite(motorDB, 0); 
    analogWrite(motorDF, 100);
  }
  
  else if (state == 'J') {  // Se o estado recebido for igual a 'J', o carro se movimenta para Trás Direita.
    analogWrite(motorLF, 0);   
    analogWrite(motorLB, 100);
    analogWrite(motorDB, 0);   
    analogWrite(motorDF, vSpeed);
  }

  else if (state == 'L') {   // Se o estado recebido for igual a 'L', o carro se movimenta para esquerda.
    analogWrite(motorLF, 0);
    analogWrite(motorLB, vSpeed);
    analogWrite(motorDB, vSpeed);
    analogWrite(motorDF, 0);
  }
  else if (state == 'R') {   // Se o estado recebido for igual a 'R', o carro se movimenta para direita.
    analogWrite(motorLF, vSpeed);
    analogWrite(motorLB, 0);
    analogWrite(motorDB, 0);
    analogWrite(motorDF, vSpeed);
  }
  else if (state == 'S') {   // Se o estado recebido for igual a 'S', o carro permanece parado.
    analogWrite(motorLF, 0);
    analogWrite(motorLB, 0);
    analogWrite(motorDB, 0);
    analogWrite(motorDF, 0);
  }


  else if (state == 'V') { // Se o estado recebido for iguala 'V', aciona a buzina.
    if (j == 0) {
      tone(buzzer, 1000);
      j = 1;
    }
    else if (j == 1) {
      noTone(buzzer);
      j = 0;
    }
    state = 'n';
  }


}

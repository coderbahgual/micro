//Carrega a biblioteca do sensor ultrassonico
#include <Ultrasonic.h>
//Define os pinos para o trigger e echo
#define pinoTrigger 2
#define pinoEcho 3
//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pinoTrigger, pinoEcho);

const int buzzer = 12; // Define o Pino 13 como pino do Buzzer.

// Define os pinos de utilização do Driver L298.
const int motorLF = 11; // motor esquerdo gira pra frente
const int motorLB = 10; // motor esquerdo gira pra tras
const int motorDB = 9;  // motor direito gira pra frente
const int motorDF = 8;  // motor direito gira pra tras

#define MAX_SPEED 200
#define MAX_SPEED_OFFSET 20

float distancia = 0;
int speedSet = 0;

#define turn_amount 500

void setup() {
  // Inicializa as portas como entrada e saída.
  pinMode(motorLF, OUTPUT);
  pinMode(motorLB, OUTPUT);
  pinMode(motorDB, OUTPUT);
  pinMode(motorDF, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Inicializa a comunicação serial em 9600 bits.
  Serial.begin(9600);
  Serial.println("Motor test!");
}

void loop() {
  float distanciaAux;
  long microsec = ultrasonic.timing();
  distancia = ultrasonic.convert(microsec, Ultrasonic::CM); // info sensor em centimetros
  delay(40);
  Serial.print("Distancia atual: ");
  Serial.println(distancia);
  moveForward();
  if (distancia <= 0.0) {
    // tone(buzzer, 440, 1000);
    digitalWrite(buzzer, LOW);
    delay(1000);
    digitalWrite(buzzer, HIGH);
    
    Serial.println("Object Detected");
    moveStop();
    delay(100);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);
    distanciaAux = ultrasonic.convert(microsec, Ultrasonic::CM); // info sensor em centimetros
    Serial.print("Distancia aux: ");
    Serial.println(distanciaAux);
    delay(200);

    if(distanciaAux >= distancia) {
      turnRight();
      moveStop();
    } else {
      turnLeft();
      turnLeft();
      moveStop();
    }
  } else {
    moveForward();
  }
}

void motores(int vMLF, int vMDF, int vMLB, int vMDB) {
  analogWrite(motorLF, vMLF);
  analogWrite(motorLB, vMLB);
  analogWrite(motorDF, vMDF);
  analogWrite(motorDB, vMDB);
}

void moveStop() {
  motores(0, 0, 0, 0);
}
  
void moveForward() {
  // motores(MAX_SPEED, 0, MAX_SPEED, 0);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) 
  // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motores(speedSet, 0, speedSet, 0);
    // motores(speedSet, 0, speedSet+MAX_SPEED_OFFSET, 0);
    delay(5);
  }
}

void moveBackward() {
  // motores(0, MAX_SPEED, 0, MAX_SPEED);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) 
  // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motores(0, speedSet, 0, speedSet);
    // motores(0, speedSet, 0, speedSet+MAX_SPEED_OFFSET);
    delay(5);
  }
}  

void turnRight() {
  Serial.println("Turning Right");
  motores(MAX_SPEED, 0, 0, MAX_SPEED);
  delay(turn_amount);
  motores(MAX_SPEED, 0, MAX_SPEED, 0);
} 
 
void turnLeft() {
  Serial.println("Turning Left");
  motores(0, MAX_SPEED, MAX_SPEED, 0);
  delay(turn_amount);
  motores(MAX_SPEED, 0, MAX_SPEED, 0);
}  

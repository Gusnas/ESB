
/*
Entrada Analogica, Saida Analogica, Saida serial
Le o pino de entrada analogica, mapeia o resultado para um intervalo entre 0
e 255 e usa o resultado para estabelecer o pulso PWM do pino de saida.
Tambem e possivel acompanhar o resultado atraves do Monitor Serial.
O circuito:
- O pino central do Potenciometro conectado ao pino analogico 0. Os pinos
lateriais do potenciometro conectados no terra e 5V.
*/
// constantes nao sao alteradas:
const int analogInPin = A0; // Entrada analogica do potenciometro

int sensorValue = 0; // leitura do potenciometro
int outputValue = 0; // leitura da saida PWM (analogica)
int leftSteer = 0;
int rightSteer = 0;
int straightSteer = 0;
int green = 11, red = 12;
float converter;
void setup() {
// inicializa a comunicacao serial:
Serial.begin(9600);
pinMode(green, OUTPUT);
pinMode(red, OUTPUT);
}
void loop() {
// faz a leitura da entrada analogica:
sensorValue = analogRead(analogInPin);

// mapeia o resultado da entrada analogica dentro do intervalo de 0 a 255:
outputValue = map(sensorValue, 0, 1023, 0, 255);

// mapeia de 256 para 180 graus, sendo 90 para direita e 90 para esquerda, apenas para obtermos o grau de esterçamento
leftSteer = map(outputValue, 0, 126, -90,-1);
straightSteer = map(outputValue, 127, 128, 0, 0);
rightSteer = map(outputValue, 129, 255, 1, 90);

// imprime o resultado no monitor serial:
/*Serial.print("sensor = " );
converter = sensorValue * 10.9481915934;
Serial.print(converter, 0);
Serial.print("\t output = ");
Serial.println(outputValue);*/

// volante virado para esquerda
if(outputValue <= 126){
  //Serial.print("We're going Left \n");
  Serial.print(leftSteer);
  Serial.print(" °\n");
  digitalWrite(green,LOW);
  digitalWrite(red,HIGH);
}
// volante virado para direita
if(outputValue >= 129){
  //Serial.print("We're going Right \n");
  Serial.print(rightSteer);
  Serial.print(" °\n");
  digitalWrite(green,HIGH);
  digitalWrite(red,LOW);
}
// volante reto com folga de 2 bits (127 e 128)
if(outputValue >= 127 && outputValue <= 128){
  //Serial.print(" We're going straight ");
  Serial.print(straightSteer);
  Serial.print(" °\n");
  digitalWrite(green,LOW);
  digitalWrite(red,LOW);
}
// Aguarda 0.5 segundos antes do proximo loop:
delay(500);
}

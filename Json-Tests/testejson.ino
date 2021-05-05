#include <ArduinoJson.h>

int steerU = 0;
int speedm = 0;
int temp = 0;


void setup() {
// inicializa a comunicacao serial:
Serial.begin(9600);
}

void volante(){
  DynamicJsonDocument steer(1024);
  steer["steerU"] = 8;
  serializeJson(steer,Serial);
  Serial.println();
}
void speedJ(){
    DynamicJsonDocument speedm(1024);
    speedm["speedm"] = 20;
    serializeJson(speedm,Serial);
    Serial.println();
}

void tempJ(){
    DynamicJsonDocument temp(1024);
    temp["temp"] = 63;
    serializeJson(temp,Serial);
    Serial.println();
}
void brake(){
  DynamicJsonDocument brakes(1024);
  brakes["brake"] = 467;
  serializeJson(brakes,Serial);
  Serial.println();
}
void loop() {
volante();
tempJ();
speedJ();
brake();
}

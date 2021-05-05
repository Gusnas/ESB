const int sensorPin = A0;  
float sensorValue = 0;     
float currentValue = 0;    
float voltsporUnidade = 0.0048875855327468; 
float ruido = 0.00;
 
void setup(){
Serial.begin(9600); 
}
 
void loop() {
  
  currentValue = 0;
  for(int i = 0; i<5000; i++){
    sensorValue = analogRead(sensorPin);
    sensorValue = (sensorValue -510)* voltsporUnidade; 
    currentValue = currentValue +(sensorValue/66)*1000; 
    delay(1);  
}
  
  currentValue = currentValue /5000;
  Serial.print("corrente = " );       
  currentValue = currentValue - ruido;
  Serial.print(currentValue, 2);  
  Serial.print("\n" );       
 
  delay(10);                     
}

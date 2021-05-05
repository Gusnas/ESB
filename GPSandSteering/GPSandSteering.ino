#include <NMEAGPS.h>
#include <NeoSWSerial.h>

static const int RXPin = 2, TXPin = 3;
NeoSWSerial gpsPort(RXPin, TXPin);
static const uint32_t GPSBaud = 9600;

const int analogInPin = A0; // Entrada analogica do potenciometro
int sensorValue = 0; // leitura do potenciometro
int outputValue = 0; // leitura da saida PWM (analogica)
int steerU = 0;

float lati;
NMEAGPS gps;
gps_fix fix;
uint8_t fixCount = 0;

void setup()
{
  Serial.begin(9600);
  gpsPort.begin(GPSBaud);

  Serial.println(F("GPS LOADING....."));
  Serial.println(F("Obtain and print lati,logi,speed,date and time"));
  Serial.println();
}

void loop()
{
  while (gps.available(gpsPort)) {
    fix = gps.read();
    if (++fixCount >= 2) {
      gpsInfo();
      potenciometro();
      fixCount = 0;
    }
  }
  if ((gps.statistics.chars < 10) && (millis() > 2000)) {
     Serial.println( F("No GPS detected: check wiring.") );
     while(true);
  }
}

void potenciometro(){
  // faz a leitura da entrada analogica:
  sensorValue = analogRead(analogInPin);
// mapeia o resultado da entrada analogica dentro do intervalo de -95 a 95:
  outputValue = map(sensorValue, 0, 1023, -95,95);
  Serial.print("Volante: ");
  Serial.print(outputValue);
  Serial.print(" graus");
  Serial.println();
}

void gpsInfo()
{
  Serial.print(F("Location: ")); 
  if (fix.valid.location) { // verifica dados de localização
    Serial.print( fix.latitude(), 5 );
    Serial.print( ',' );
    Serial.print( fix.longitude(), 5 );
  } else {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Speed: ")); 
  if (fix.valid.speed) { // verifica velocidade
    Serial.print(fix.speed_kph());
    Serial.print(F(" KMPH "));
  } else {
    Serial.print(F("INVALID"));
  }

  // Shift the date/time to local time
  NeoGPS::clock_t localSeconds;
  NeoGPS::time_t  localTime;
  if (fix.valid.date && fix.valid.time) {
    using namespace NeoGPS; // save a little typing below...

    localSeconds = (clock_t) fix.dateTime; // convert structure to a second count
    localSeconds += 5 * SECONDS_PER_HOUR + 30 * SECONDS_PER_MINUTE; // shift timezone
    localTime = localSeconds;              // convert back to a structure
  }

  Serial.print(F("  Date : "));
  if (fix.valid.date) {
    Serial.print(localTime.month);
    Serial.print('/');
    Serial.print(localTime.date);
    Serial.print('/');
    Serial.print(localTime.year);
  } else {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Time : "));
  if (fix.valid.time) {
    Serial.print(localTime.hours);
    Serial.print(':');
    if (localTime.minutes < 10) Serial.print('0');
    Serial.print(localTime.minutes);
    Serial.print(':');
    if (localTime.seconds < 10) Serial.print(F("0"));
    Serial.print(localTime.seconds);
  } else {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}

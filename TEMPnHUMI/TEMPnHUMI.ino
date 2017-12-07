
#include "DHT.h"
#include <Adafruit_Sensor.h>

#define DHTPIN D4 // what pin we're connected to
#define DHTTYPE DHT22 // DHT 11 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
Serial.begin(9600); 
Serial.println("DHTxx test!");
dht.begin();
}

void loop() {
  Serial.println("why not show");
   int H = dht.readHumidity();
   Serial.println(H);
   int T = dht.readTemperature();
   Serial.println(T);
   delay(5000);
}

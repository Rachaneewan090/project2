#include "DHT.h"
#include <Adafruit_Sensor.h>
#include <ESP8266WiFi.h>

#define DHTPIN D4 // what pin we're connected to
#define DHTTYPE DHT22 // DHT 11 

//setup wifi
const char* ssid     = "PAINAIMA";
const char* password = "0805205425";

DHT dht(DHTPIN, DHTTYPE);

void setup() {
Serial.begin(9600); 
//DHT
Serial.println("DHTxx test!");
dht.begin();

//Connect wifi
Serial.println("Starting...");
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) 
  {
      delay(250);
      Serial.print(".");
   }
Serial.println("WiFi connected");  
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
}

void loop() {
  Serial.println("why not show");
   int H = dht.readHumidity();
   Serial.println(H);
   int T = dht.readTemperature();
   Serial.println(T);
   delay(5000);
}

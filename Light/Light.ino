#define PIN A0
#include <ESP8266WiFi.h>

//setup wifi
const char* ssid     = "PAINAIMA";
const char* password = "0805205425";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

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
  // put your main code here, to run repeatedly:
  int light = analogRead(PIN);
  Serial.println(light);
  delay(10000);

}

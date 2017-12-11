#include <MicroGear.h>
#include <ESP8266WiFi.h>
#include "DHT.h"

const char* ssid     = "PAINAIMA";
const char* password = "0805205425";

#define APPID   "DemoKeppa"
#define KEY     "MiMqaX43JNzWoux"
#define SECRET  "wizMipeH7aoZydvLbOVGcueai"

#define ALIAS   "DHT22"
#define TargetWeb "HTML_web"

#define D4 2   // TXD1
#define DHTPIN D4     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;
MicroGear microgear(client);

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) 
{
    Serial.print("Incoming message --> ");
    msg[msglen] = '\0';
    Serial.println((char *)msg);
}//เป็นการพิมพ์ข้อความที่ได้รับออกทางพอร์ต Serial

void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) 
{
    Serial.println("Connected to NETPIE...");
    microgear.setAlias(ALIAS);
}//เป็นการพิมพ์สถานะการเชื่อมต่อสำเร็จไปยังพอร์ต Serial และตั้งชื่อเรียกให้กับอุปกรณ์

void setup() 
{
     /* Event listener */
    microgear.on(MESSAGE,onMsghandler);
    microgear.on(CONNECTED,onConnected);

    dht.begin();
    Serial.begin(115200);
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

    microgear.init(KEY,SECRET,ALIAS);//สั่งให้ Microgear ต่อกับ NETPIE
    microgear.connect(APPID);
}

void loop() 
{
    if (microgear.connected())
    {
       microgear.loop();
       Serial.println("connected");

       float Humidity = dht.readHumidity();
       float Temp = dht.readTemperature();  // Read temperature as Celsius (the default)
       String data = "/" + String(Humidity) + "/" + String(Temp);
       char msg[128];
       data.toCharArray(msg,data.length());
       Serial.println(msg);    

       microgear.chat(TargetWeb , msg);
    }
   else 
   {
    Serial.println("connection lost, reconnect...");
    microgear.connect(APPID);
   }
    delay(1500);
}

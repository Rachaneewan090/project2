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

#define FEEDID "KEPPAFeed"
#define APIKEY "DtDVWCl0S4vQgKICiMhEEXg6gqyU4CNU"

#define D4 2   // TXD1
#define DHTPIN D4     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;
MicroGear microgear(client);

int timer = 0;
char strhumi[32];
char strTemp[32];

int humid;
int temp;

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
       delay(500);
       Serial.print(".");
    }

    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    microgear.init(KEY,SECRET,ALIAS);//สั่งให้ Microgear ต่อกับ NETPIE
    microgear.connect(APPID);
}

void loop(){
    if (microgear.connected()) {
        Serial.println("connected");
        microgear.loop();

        if (timer >= 1000) {
            humid = dht.readHumidity();
            temp = dht.readTemperature();
            
            sprintf(strhumi,"%d",humid);
            Serial.println(strhumi);
            Serial.print("Sending -->");
            microgear.publish("/dht/humi",strhumi);

            //temp
            sprintf(strTemp,"%d",temp);
            Serial.println(strTemp);
            Serial.print("Sending -->");
            microgear.publish("/dht/temp",strTemp);
            timer = 0;

            if (isnan(humid) || isnan(temp)){
                Serial.println("Failed to read from DHT sensor");
                }else{
                  //สร้างข้อความส่งไปที่ feed
                  String msgToFeed = "{\"humi\":"+(String)humid+",\"temp\":"+(String)temp+"}";
                  Serial.println(msgToFeed);
                  microgear.writeFeed(FEEDID,msgToFeed);
                  }//else
        } 
        else timer += 100;
    }
    else {
        Serial.println("connection lost, reconnect...");
        if (timer >= 5000) {
            microgear.connect(APPID);
            timer = 0;
        }
        else timer += 100;
    }
    delay(1000);
}

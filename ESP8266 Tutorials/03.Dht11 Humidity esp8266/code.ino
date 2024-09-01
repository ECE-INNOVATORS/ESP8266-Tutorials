#define BLYNK_TEMPLATE_ID "TMPL3LjivlFPp"
#define BLYNK_TEMPLATE_NAME "HUMIDITY"
#define BLYNK_AUTH_TOKEN "SD4fm-6Rs0JB6mBIJEBqKZlZByox3fx7"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
char ssid[] = "-----";   //your wifi name//
char pass[] = "-----";   //your wifi password//
#define DHTPIN D1
#define DHTTYPE DHT11
DHT dht (DHTPIN, DHTTYPE);
void setup()
 {
Serial.begin(9600);
Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
dht.begin();
}
void loop() {
Blynk.run();
float h = dht.readHumidity();
Blynk.virtualWrite(V0, h);
delay(2000);
}


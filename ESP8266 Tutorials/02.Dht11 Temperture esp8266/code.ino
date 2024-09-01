#define BLYNK_TEMPLATE_ID "//copy your TEPLATE_ID//"
#define BLYNK_TEMPLATE_NAME "//copy your TEPLATE_NAME//"
#define BLYNK_AUTH_TOKEN "//copy yoUR AUTH TOKEN Here//"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// Your network credentials
char ssid[] = "-----";   //your wifi name//
char pass[] = "-----";   //your wifi password//

// Blynk template details


// DHT sensor settings
#define DHTPIN D1  // Pin where the DHT11 is connected
#define DHTTYPE DHT11  // DHT 11
DHT dht(DHTPIN, DHTTYPE);

// Timer settings
BlynkTimer timer;

void sendSensor() {
  float tC = dht.readTemperature(); // Read temperature in Celsius
  float tF = dht.readTemperature(true); // Read temperature in Fahrenheit

  if (isnan(tC) || isnan(tF)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V0, tC); // Temperature in Celsius to virtual pin V5 (Gauge)
  Blynk.virtualWrite(V1, tF); // Temperature in Fahrenheit to virtual pin V6 (Label)
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  dht.begin();
  
  // Setup a function to be called every 2 seconds
  timer.setInterval(2000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}


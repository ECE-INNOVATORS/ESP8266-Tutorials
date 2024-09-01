#define BLYNK_TEMPLATE_ID "//copy your TEPLATE_ID//"
#define BLYNK_TEMPLATE_NAME "//copy your TEPLATE_NAME//"
#define BLYNK_AUTH_TOKEN "//copy yoUR AUTH TOKEN Here//"


#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <NewPing.h>  // Include the NewPing library

// Your WiFi credentials
const char* ssid = "";
const char* password = "";

// DHT sensor settings
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Ultrasonic Sensor settings
#define TRIGGER_PIN D1
#define ECHO_PIN D2
#define MAX_DISTANCE 200

// Initialize NewPing library for ultrasonic sensor
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// Soil moisture sensor settings
#define SOIL_MOISTURE_PIN A0

// Timer for scheduling sensor readings
BlynkTimer timer;

void sendSensorData() {
  // Read and send DHT11 data
  float tC = dht.readTemperature();
  float tF = dht.readTemperature(true);
  float humidity = dht.readHumidity();

  if (isnan(tC) || isnan(tF) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Blynk.virtualWrite(V0, tC);
    Blynk.virtualWrite(V1, tF);
    Blynk.virtualWrite(V2, humidity);
  }

  // Read and send ultrasonic distance data
  unsigned int distance = sonar.ping_cm();
  Blynk.virtualWrite(V3, distance);

  // Read and send soil moisture data
  int soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);
  Blynk.virtualWrite(V4, soilMoistureValue);

  // Print values to Serial Monitor for debugging
  Serial.print("Temperature (C): ");
  Serial.print(tC);
  Serial.print(" | Temperature (F): ");
  Serial.print(tF);
  Serial.print(" | Humidity: ");
  Serial.print(humidity);
  Serial.print(" | Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Soil Moisture: ");
  Serial.println(soilMoistureValue);
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  dht.begin();
  timer.setInterval(2000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}
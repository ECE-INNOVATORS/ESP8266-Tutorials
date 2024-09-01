#define BLYNK_TEMPLATE_ID "//copy your TEPLATE_ID//"
#define BLYNK_TEMPLATE_NAME "//copy your TEPLATE_NAME//"
#define BLYNK_AUTH_TOKEN "//copy yoUR AUTH TOKEN Here//"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Replace with your network credentials
const char* ssid = "//your ssid name//";
const char* password = "//ssid password//";

// Blynk template and authentication


// Pin where the sensor is connected
#define SOIL_MOISTURE_PIN A0

void setup() {
  // Start serial communication
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  // Initialize Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
}

void loop() {
  // Read soil moisture value
  int sensorValue = analogRead(SOIL_MOISTURE_PIN);
  
  // Print sensor value to Serial Monitor
  Serial.print("Soil Moisture Value: ");
  Serial.println(sensorValue);

  // Send soil moisture value to Blynk
  Blynk.virtualWrite(V0, sensorValue);  // For Gauge
  Blynk.virtualWrite(V1, sensorValue);  // For Label

  // Run Blynk
  Blynk.run();

  // Delay before next reading
  delay(2000);
}

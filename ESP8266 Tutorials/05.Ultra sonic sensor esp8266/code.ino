#define BLYNK_TEMPLATE_ID "TMPL3ZRe6htA6"
#define BLYNK_TEMPLATE_NAME "ultrasonic"
#define BLYNK_AUTH_TOKEN "TyPKF28OYqJZwrVfh5c3DPqXsyXlIncP"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <NewPing.h>

// Your WiFi credentials
char ssid[] = "---------";   // Replace with your WiFi Name
char pass[] = "---------";  // Replace with your WiFi password

// Ultrasonic Sensor pins

#define ECHO_PIN D2     // D2
#define TRIGGER_PIN D1 // D1
#define MAX_DISTANCE 200  // Maximum distance we want to measure (in centimeters)

// Initialize NewPing library
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

BlynkTimer timer;

void setup() {
  // Debug console
  Serial.begin(115200);

  // Connect to Wi-Fi and Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void sendSensor() {
  // Measure distance
  unsigned int distance = sonar.ping_cm();

  // Send distance to Blynk app
  Blynk.virtualWrite(V0, distance);  // Gauge widget
  Blynk.virtualWrite(V1, distance);  // Label widget

  // Print distance to Serial Monitor for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}
void loop() {
  Blynk.run();
  timer.run();  // Initiates BlynkTimer
}


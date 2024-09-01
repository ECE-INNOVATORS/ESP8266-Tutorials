#define BLYNK_TEMPLATE_ID "//copy your TEPLATE_ID//"
#define BLYNK_TEMPLATE_NAME "//copy your TEPLATE_NAME//"
#define BLYNK_AUTH_TOKEN "//copy yoUR AUTH TOKEN Here//"

#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Blynk credentials
char auth[] = "//copy your auth token//"; // Replace with your Blynk Auth Token
char ssid[] = "//your ssid name//";       // Replace with your Wi-Fi SSID
char pass[] = "//ssid password//";   // Replace with your Wi-Fi Password

// DHT sensor settings
#define DHTPIN 2       // Pin connected to the DHT11 data pin (D4 on ESP8266)
#define DHTTYPE DHT11  // Define the type of DHT sensor

DHT dht(DHTPIN, DHTTYPE);

// Motor control pins
int motor1Pin1 = D6; // Change to your chosen pin
int motor1Pin2 = D7; // Change to your chosen pin
int enable1Pin = D2; // Change to your chosen pin

// Blynk virtual pins
#define VIRTUAL_PIN_FAN_SPEED V1  // Virtual pin for fan speed
#define VIRTUAL_PIN_TEMPERATURE V2 // Virtual pin for temperature

void setup() {
  // Set pins as outputs
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  // Start serial communication
  Serial.begin(115200);

  // Initialize DHT sensor
  dht.begin();

  // Initialize Blynk
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  // Blynk.run() should be called frequently to process incoming commands
  Blynk.run();

  // Read temperature from DHT11
  float temperature = dht.readTemperature();

  // Check if the reading is valid
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Map temperature (30°C to 35°C) to PWM percentage (0 to 100%)
  int fanSpeedPercentage = map(temperature, 30, 35, 0, 100);
  
  // Constrain fan speed to valid range
  fanSpeedPercentage = constrain(fanSpeedPercentage, 0, 100);

  // Calculate duty cycle from percentage
  int dutyCycle = map(fanSpeedPercentage, 0, 100, 0, 255);

  // Display temperature and fan speed percentage
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Fan Speed: ");
  Serial.print(fanSpeedPercentage);
  Serial.println("%");

  // Move the DC motor forward with variable speed
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  analogWrite(enable1Pin, dutyCycle);

  // Update Blynk app with temperature and fan speed percentage
  Blynk.virtualWrite(VIRTUAL_PIN_TEMPERATURE, temperature);
  Blynk.virtualWrite(VIRTUAL_PIN_FAN_SPEED, fanSpeedPercentage);

  delay(2000); // Adjust the delay as needed

  // Stop the DC motor
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  analogWrite(enable1Pin, 0); // Turn off PWM

  delay(1000); // Adjust the delay as needed
}


// Blynk credentials
#define BLYNK_TEMPLATE_ID "//copy your TEPLATE_ID//"
#define BLYNK_TEMPLATE_NAME "//copy your TEPLATE_NAME//"
#define BLYNK_AUTH_TOKEN "//copy yoUR AUTH TOKEN Here//"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Replace these with your network credentials
char ssid[] = "//YOUR SSID ";
char pass[] = "//SSID PASSWORD//";



// Define the relay control pin
const int relayPin = D1;

// Function to control relay
BLYNK_WRITE(V5) {
  int pinValue = param.asInt(); // Get the value from the button
  digitalWrite(relayPin, pinValue); // Control the relay
}

void setup() {
  // Start serial communication
  Serial.begin(115200);

  // Initialize relay pin as output
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Ensure relay is off initially

  // Connect to Wi-Fi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  // Initialize Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run(); // Run Blynk
}


#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""// Replace with your BLYNK_AUTH_TOKEN , BLYNK_TEMPLATE_NAME , BLYNK_TEMPLATE_ID

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

// Your WiFi credentials
char ssid[] = "";
char pass[] = "";// Replace with your WiFi password


// Servo instance
Servo myservo;
int servoPin = D1;

void setup()
{
  // Debug console
  Serial.begin(115200);

  // Blynk begin
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Attach the servo to the pin
  myservo.attach(servoPin);
}

BLYNK_WRITE(V0)
{
  int sliderValue = param.asInt();  // Get the value from the slider (0 to 100)
  int servoAngle = map(sliderValue, 0, 100, 0, 180);  // Map slider value to servo angle (0 to 180 degrees)
  myservo.write(servoAngle);  // Set the servo position
}

void loop()
{
  Blynk.run();
}

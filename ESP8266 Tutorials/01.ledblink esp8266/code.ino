#define BLYNK_TEMPLATE_ID "TMPL30pnLH92m"
#define BLYNK_TEMPLATE_NAME "led blink"
#define BLYNK_AUTH_TOKEN "dni9yr0rGjlVcgkEJSQ18Qewd9rjLEdA"


#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char ssid[] = "puru 06";
char pass[] = "20062008";

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(D2, OUTPUT);
}

void loop()
{
  Blynk.run();
}

BLYNK_WRITE(V0)
{
  int pinValue = param.asInt(); // Get value as integer

  if (pinValue == 1)
  {
    digitalWrite(D2, HIGH); // Turn LED on
  }
  else
  {
    digitalWrite(D2, LOW); // Turn LED off
  }
}


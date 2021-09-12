#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <WiFiClientSecure.h>

// Magie die nodig is om versie als string en niet als float te gebruiken
#define STRINGIFY(s) STRINGIFY1(s)
#define STRINGIFY1(s) #s
#ifdef VERSION
const char* version = STRINGIFY(VERSION);
#else
const char* version = "";
#endif

const char *ssid = "Baron-iot";
const char *password = "U'o0U,#bWk$f";

void connect_wifi();
unsigned long previousMillis_2 = 0;
unsigned long previousMillis = 0; // will store last time LED was updated
const long interval = 60000;
const long mini_interval = 1000;

void repeatedCall()
{
  // unsigned long currentMillis = millis();
  // if ((currentMillis - previousMillis) >= interval)
  // {
  //   // save the last time you blinked the LED
  //   previousMillis = currentMillis;
  //   // setClock();
  //   // FirmwareUpdate();
  // }

  // if ((currentMillis - previousMillis_2) >= mini_interval)
  // {
  //   previousMillis_2 = currentMillis;
  //   Serial.print(" Active fw version:");
  //   Serial.println(VERSION);
  //   if (WiFi.status() != WL_CONNECTED)
  //     connect_wifi();
  // }
}

void setup()
{
  Serial.begin(9600);
  Serial.println("");
  Serial.print("Version: ");
  Serial.println(version);

  WiFi.mode(WIFI_STA);
  // connect_wifi();
  // setClock();
}
void loop()
{
  repeatedCall();
}

void connect_wifi()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("O");
  }
  Serial.println("Connected to WiFi");
}
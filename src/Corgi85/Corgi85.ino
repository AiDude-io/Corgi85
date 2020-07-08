#include <Arduino.h>

#include <ESP8266WiFi.h>      //ESP8266 Core WiFi Library (you most likely already have this in your sketch)
#include <DNSServer.h>        //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h> //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>      //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

#include "corgi85_utility.h"
#include "modules/CorgiIFTTT.hpp"
#include "modules/CorgiLine.hpp"
#include "modules/Corgi85_blynk.hpp"
#include "modules/Corgi85_thingspeak.hpp"
#include <vector>

CORGI85 corgi85(&Serial);

void setup()
{

  Serial.begin(115200);
  Serial.println("ESP8255 Starting");
  WiFiManager wifiManager;

  while (WiFi.status() != WL_CONNECTED)
  {
    int count = 0;
    int re_autoConnect = 0;

    while (WiFi.status() != WL_CONNECTED)
    {
      count++;
      delay(500);
      if (count >= 20)
      {
        re_autoConnect = 1;
        break;
      }
    }

    if (re_autoConnect)
    {
      if (!wifiManager.startConfigPortal("Corgi_AutoConnect"))
      {
        Serial.println("failed to connect and hit timeout");
        delay(3000);
        //reset and try again, or maybe put it to deep sleep
        ESP.reset();
        delay(5000);
      }
    }
  }
  Serial.println("WIFI Connected");

  corgi85.addModule(new CorgiIFTTT());
  corgi85.addModule(new CorgiLine());
  corgi85.addModule(new Corgi85_blynk());
  corgi85.addModule(new CorgiThingSpeak());

  corgi85.setup();
  // corgi85.printModulesList();
  // Serial.flush();
  Serial.println("Setup Finlish");
}
uint32_t count = 0;
void loop()
{
  corgi85.loop();
  delay(1);
}

#include <Arduino.h>

#include <ESP8266WiFi.h>      //ESP8266 Core WiFi Library (you most likely already have this in your sketch)
#include <DNSServer.h>        //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h> //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>      //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

#include "corgi85_utility.h"
#include "modules/CorgiIFTTT.hpp"
#include "modules/CorgiLine.hpp"
#include "modules/Corgi85_blynk.hpp"
#include <vector>

CORGI85 corgi85(&Serial);

void setup()
{
  delay(2000);
  Serial.begin(115200);

  WiFiManager wifiManager;
  if (!wifiManager.autoConnect("Corgi_AutoConnect"))
  {
    Serial.println("failed to connect, we should reset as see if it connects");
    delay(3000);
    ESP.reset();
    delay(5000);
  }
  corgi85.addModule(new CorgiIFTTT());
  corgi85.addModule(new CorgiLine());
  corgi85.addModule(new Corgi85_blynk());
}

void loop()
{
  corgi85.loop();
  // corgi85.printModulesList();
  delay(20);
}

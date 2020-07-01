

#ifndef CORGI85_BLYNK_H
#define CORGI85_BLYNK_H

#include <vector>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

class CORGI85_BLINK
{
public:
    String auth = "16bfRLyckrO9iRtRLfsVqF9aCnPkBdVK";
    String host = "blynk-cloud.com";
    unsigned int port = 8080;
    uint8_t initial = 0;

    // uint8_t Blynk_virtualWrite_float(uint8_t vir_pin, int32_t value);
    // uint8_t Blynk_virtualWrite_string(uint8_t vir_pin, float value);
    // uint8_t Blynk_virtualWrite_long(uint8_t vir_pin, long unsigned int value);
    // uint8_t Blynk_VirtualRead(uint8_t vir_pin, uint8_t value);
    // uint8_t Blynk_Set_Property(uint8_t vir_pin, uint8_t value);

    // uint8_t Blynk_Set_auth(String value);
    // uint8_t Blynk_Set_host(String value);
    // uint8_t Blynk_Set_port(unsigned int value);

private:
    uint8_t httpRequest(const String &method,
                        const String &request,
                        String &response);
    WiFiClient client;
};

#endif
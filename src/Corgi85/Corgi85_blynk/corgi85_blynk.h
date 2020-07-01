

#ifndef CORGI85_BLYNK_H
#define CORGI85_BLYNK_H
#include <vector>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
enum corgi85_blynk_mode
{
    stop,
    initialze,
    run
};

class CORGI85_BLINK
{
public:
    char *auth = "16bfRLyckrO9iRtRLfsVqF9aCnPkBdVK";

    void loop(void);
    uint8_t Blynk_virtualWrite(uint8_t vir_pin, int16_t value);
    uint8_t Blynk_virtualWrite(uint8_t vir_pin, int32_t value);
    uint8_t Blynk_virtualWrite(uint8_t vir_pin, float value);
    uint8_t Blynk_virtualWrite(uint8_t vir_pin, long unsigned int value);
    uint8_t Blynk_VirtualRead(uint8_t vir_pin, uint8_t value);

    uint8_t Blynk_Set_Property(uint8_t vir_pin, uint8_t value);

    String response;

private:
    corgi85_blynk_mode mode = stop;

    const char *host = "blynk-cloud.com";
    unsigned int port = 8080;
    uint8_t httpRequest(const String &method,
                        const String &request,
                        String &response);
    WiFiClient client;
};

void DoBlynk(std::vector<String> data);

#endif
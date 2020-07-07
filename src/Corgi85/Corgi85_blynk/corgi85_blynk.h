

#ifndef CORGI85_BLYNK_H
#define CORGI85_BLYNK_H

#include <vector>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

class CORGI85_BLINK
{
public:
    String auth = "";
    String host = "blynk-cloud.com";
    unsigned int port = 8080;
    uint8_t initial = 0;
    uint8_t event = 0;
    float virtual_pin[32];
    
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

CORGI85_BLINK corgi85_blynk;

BLYNK_WRITE(V0)
{
    corgi85_blynk.virtual_pin[V0] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V1)
{
    corgi85_blynk.virtual_pin[V1] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V2)
{
    corgi85_blynk.virtual_pin[V2] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V3)
{
    corgi85_blynk.virtual_pin[V3] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V4)
{
    corgi85_blynk.virtual_pin[V4] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V5)
{
    corgi85_blynk.virtual_pin[V5] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V6)
{
    corgi85_blynk.virtual_pin[V6] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V7)
{
    corgi85_blynk.virtual_pin[V7] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V8)
{
    corgi85_blynk.virtual_pin[V8] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V9)
{
    corgi85_blynk.virtual_pin[V9] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V10)
{
    corgi85_blynk.virtual_pin[V10] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V11)
{
    corgi85_blynk.virtual_pin[V11] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V12)
{
    corgi85_blynk.virtual_pin[V12] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V13)
{
    corgi85_blynk.virtual_pin[V13] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V14)
{
    corgi85_blynk.virtual_pin[V14] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V15)
{
    corgi85_blynk.virtual_pin[V15] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V16)
{
    corgi85_blynk.virtual_pin[V16] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V17)
{
    corgi85_blynk.virtual_pin[V17] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V18)
{
    corgi85_blynk.virtual_pin[V18] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V19)
{
    corgi85_blynk.virtual_pin[V19] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V20)
{
    corgi85_blynk.virtual_pin[V20] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V21)
{
    corgi85_blynk.virtual_pin[V21] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V22)
{
    corgi85_blynk.virtual_pin[V22] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V23)
{
    corgi85_blynk.virtual_pin[V23] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V24)
{
    corgi85_blynk.virtual_pin[V24] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V25)
{
    corgi85_blynk.virtual_pin[V25] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V26)
{
    corgi85_blynk.virtual_pin[V26] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V27)
{
    corgi85_blynk.virtual_pin[V27] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V28)
{
    corgi85_blynk.virtual_pin[V28] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V29)
{
    corgi85_blynk.virtual_pin[V29] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V30)
{
    corgi85_blynk.virtual_pin[V30] = param.asFloat();
    corgi85_blynk.event = 1;
}
BLYNK_WRITE(V31)
{
    corgi85_blynk.virtual_pin[V31] = param.asFloat();
    corgi85_blynk.event = 1;
}

#endif
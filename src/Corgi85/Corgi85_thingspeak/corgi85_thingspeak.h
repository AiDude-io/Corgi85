#ifndef CORGI85_THINGSPEAK_H
#define CORGI85_THINGSPEAK_H

#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

WiFiClient client;

char *api_key;
unsigned long channel_id;
bool init_success = false;

void ts_init()
{
  if (!init_success)
  {
    Serial.println("ThingSpeak init ...");
    ThingSpeak.begin(client);
    Serial.println("ThingSpeak init success.");
    init_success = true;
  }
}

void ts_account(char *input_api_key, unsigned long input_channel_id)
{
  Serial.println("ThingSpeak account setup ...");
  strcpy(api_key, input_api_key);
  channel_id = input_channel_id;
  Serial.println("ThingSpeak account setup success.");
}

void ts_write_field(uint8_t field, uint8_t value)
{
  Serial.println("ThingSpeak write field ...");
  int response = ThingSpeak.writeField(channel_id, field, value, (char *)&api_key);
  if (response == 200)
  {
    Serial.println("Channel update successful.");
  }
}
#endif

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
  Serial.println(strlen(input_api_key));
  api_key = (char *)malloc(strlen(input_api_key) + 1);
  strcpy(api_key, input_api_key);
  Serial.print("after strcpy api_key : ");
  Serial.println(api_key);
  channel_id = input_channel_id;
  Serial.println("ThingSpeak account setup success.");
}

void ts_write_field(uint8_t field, uint8_t value)
{
  Serial.println("ThingSpeak write field ...");
  Serial.print("channel_id : ");
  Serial.println(channel_id);
  Serial.print("field : ");
  Serial.println(field);
  Serial.print("value : ");
  Serial.println(value);
  Serial.print("api_key : ");
  Serial.println(api_key);
  int response = ThingSpeak.writeField(channel_id, field, value, api_key);

  if (response == 200)
  {
    Serial.println("Channel update successful.");
  }
}
#endif

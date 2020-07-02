#include <vector>
#include <Arduino.h>
#include "corgi85_blynk.h"


void DoBlynk(std::vector<String> data)
{
  int func_no = String(data[0]).toInt();

  switch (func_no)
  {
  case 0: // set auth
  {
    Blynk.config(String(data[1]).c_str());
  }
  break;

  case 1: // set host
  {
    Blynk.config(String(data[1]).c_str());
    uint8_t vir_pin = String(data[1]).toInt();
    int value = String(data[1]).toInt();
    Blynk.virtualWrite(vir_pin, value);
  }
  case 2: // set port
  {
    port  = String(data[1]).toInt();
    String value = String(data[1]);
    Blynk.virtualWrite(vir_pin, value);
  }
  case 3:
  {
    uint8_t vir_pin = String(data[1]).toInt();
    float value = String(data[1]).toFloat();
    Blynk.virtualWrite(vir_pin, value);
  }
  break;
  }

  //String x = String(static_cast<char *>(args));
}

uint8_t CORGI85_BLINK::Blynk_virtualWrite(uint8_t vir_pin, int16_t value)
{
    Blynk.virtualWrite(vir_pin, value);
    return 1;
}

uint8_t CORGI85_BLINK::Blynk_virtualWrite(uint8_t vir_pin, int32_t value)
{
    Blynk.virtualWrite(vir_pin, value);
    return 1;
}

uint8_t CORGI85_BLINK::Blynk_virtualWrite(uint8_t vir_pin, float value)
{
    Blynk.virtualWrite(vir_pin, value);
    return 1;
}

uint8_t CORGI85_BLINK::Blynk_virtualWrite(uint8_t vir_pin, long unsigned int value)
{
    Blynk.virtualWrite(vir_pin, value);
    Serial.println(value);
    return 1;
}

void CORGI85_BLINK::loop(void)
{
    Blynk.virtualWrite(V0, millis() / 1000);

    switch (mode)
    {
    case stop:
        /* code */

        break;
    case initialze:
        /* code */
        if (WiFi.status() != WL_CONNECTED)
        {
            break;
        }
        Blynk.config(auth);
        mode = run;
        break;

    case run:
        /* code */
        Blynk.run();

        break;

    default:
        break;
    }
}

uint8_t CORGI85_BLINK::httpRequest(const String &method,
                                   const String &request,
                                   String &response)
{
    Serial.print(F("Connecting to "));
    Serial.print(host);
    Serial.print(":");
    Serial.print(port);
    Serial.print("... ");
    if (client.connect(host, port))
    {
        Serial.println("OK");
    }
    else
    {
        Serial.println("failed");
        return false;
    }

    client.print(method);
    client.println(F(" HTTP/1.1"));
    client.print(F("Host: "));
    client.println(host);
    client.println(F("Connection: close"));
    if (request.length())
    {
        client.println(F("Content-Type: application/json"));
        client.print(F("Content-Length: "));
        client.println(request.length());
        client.println();
        client.print(request);
    }
    else
    {
        client.println();
    }

    //Serial.println("Waiting response");
    int timeout = millis() + 5000;
    while (client.available() == 0)
    {
        if (timeout - millis() < 0)
        {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return false;
        }
    }

    //Serial.println("Reading response");
    int contentLength = -1;
    while (client.available())
    {
        String line = client.readStringUntil('\n');
        line.trim();
        line.toLowerCase();
        if (line.startsWith("content-length:"))
        {
            contentLength = line.substring(line.lastIndexOf(':') + 1).toInt();
        }
        else if (line.length() == 0)
        {
            break;
        }
    }

    //Serial.println("Reading response body");
    response = "";
    response.reserve(contentLength + 1);
    while (response.length() < contentLength && client.connected())
    {
        while (client.available())
        {
            char c = client.read();
            response += c;
        }
    }
    client.stop();
    return true;
}
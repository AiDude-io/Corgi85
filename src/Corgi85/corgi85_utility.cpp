#include <Arduino.h>
#include "corgi85_utility.h"
#include "StringSplitter.h" //https://github.com/aharshac/StringSplitter
#include <ESP8266WiFi.h>

CORGI85::CORGI85(HardwareSerial *Serial) //read the uart signal by hardware uart,such as D0
{
  corgi_serial = Serial;
  receivedFlag = 0;
}

uint8_t CORGI85::checkSum(uint8_t array[], uint8_t length)
{
  uint8_t sum = 0;
  for (int i = 1; i < length - 1; i++)
  {
    sum += array[i];
  }
  sum = (~sum) + 1;
  return sum;
}

void CORGI85::printModulesList()
{
  std::map<const char *, CorgiModule *>::iterator it = this->moduleList.begin();
  int i = 0;
  while (it != this->moduleList.end())
  {
    const char *word = it->first;
    Serial.printf("[%d] = %s\r\n", i, word);
    i++;
    it++;
  }
}

bool CORGI85::addModule(CorgiModule *module)
{
  this->moduleList[module->name()] = module;
  return true;
}

// uint8_t CORGI85::loop(void)
// {
//   uint8_t received_command = run();
//   if (received_command != 0 && registered_callback.count("received_command") > 0)
//   {
//     Callback cb = registered_callback["received_command"];
//     //(*cb)(123,(void *)"sssss");
//     String a = "!23";
//     String b = "456";
//     std::vector<String> bbb;
//     bbb.push_back(a);
//     bbb.push_back(b);
//     (*cb)(bbb);
//   }
//   return 1;
// }

uint8_t CORGI85::loop(void) //new data was recevied
{
  std::map<const char *, CorgiModule *>::iterator it = this->moduleList.begin();
  int i = 0;
  while (it != this->moduleList.end())
  {
    CorgiModule *module = it->second;
    module->loop();

    // const char *word = it->first;
    // Serial.printf("[%d] = %s\r\n", i, word);
    // i++;
    it++;
  }

  while (corgi_serial->available())
  {

    switch (current_mode)
    {
    case serial_string: // command // module name -------------\r
    {
      char s = corgi_serial->read();
      _data += s;
      if (s == '\r')
      {
        std::map<const char *, CorgiModule *>::iterator it = this->moduleList.begin();
        while (it != this->moduleList.end())
        {
          String word = it->first;
          if (_data.indexOf(word) == 0)
          {
            module = it->second;
            module->cmd(_data);
          }
          it++;
        }

        // command // module name, fn , "RAW_DATA", data size,\r-----------------data------------------
        if (_data.indexOf("RAW_DATA") != -1)
        {
          StringSplitter *splitter = new StringSplitter(_data, ',', 4);
          data_length = (int32_t)String(splitter->getItemAtIndex(3)).toInt();
          current_mode = serial_raw;
          delete splitter;
          _raw = "";
        }

        if (_data.indexOf("WIFI_CHECK") == 0)
        {
          if (WiFi.status() == WL_CONNECTED)
          {
            Serial.print("1\r");
          }
          else
          {
            Serial.print("0\r");
          }
        }

        if (_data.indexOf("RESET") == 0)
        {
          ESP.reset();
        }
        _data = "";
      }
    }
    break;

    case serial_raw:
    {
      _raw += corgi_serial->read();
      data_length--;
      if (data_length <= 0)
      {
        module->raw(_raw, data_length);
        current_mode = serial_string;
      }
    }
    break;
    }
  }
  return 0;
}

uint8_t CORGI85::setup(void) //new data was recevied
{
  std::map<const char *, CorgiModule *>::iterator it = this->moduleList.begin();
  int i = 0;
  while (it != this->moduleList.end())
  {
    CorgiModule *module = it->second;
    module->setup();
    it++;
  }
  return 0;
}

uint8_t CORGI85::buffer_avaliable(void) //new data was recevied
{
  uint8_t length = 0;

  if (pointer_head >= pointer_tail)
    length = pointer_head - pointer_tail;
  else
    length = (255 - pointer_tail) + pointer_head;

  return length;
}

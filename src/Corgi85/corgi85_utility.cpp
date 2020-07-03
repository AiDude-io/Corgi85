#include <Arduino.h>
#include "corgi85_utility.h"

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
    char s = corgi_serial->read();
    _raw += s;
    if (s == '\r')
    {
      std::map<const char *, CorgiModule *>::iterator it = this->moduleList.begin();
      while (it != this->moduleList.end())
      {
        String word = it->first;
        if (_raw.indexOf(word) == 0)
        {
          CorgiModule *module = it->second;
          module->cmd(_raw);
        }
        it++;
      }
      _raw = "";
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

    // const char *word = it->first;
    // Serial.printf("[%d] = %s\r\n", i, word);
    // i++;
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

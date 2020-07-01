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

void CORGI85::printModulesList() {
  std::map<const char*, CorgiModule*>::iterator it = this->moduleList.begin();
  int i = 0;
  while (it != this->moduleList.end())
  {
      const char* word = it->first;
      Serial.printf("[%d] = %s\r\n", i, word);
      i++;
      it++;
  }
}

void CORGI85::registerCallback(String comm,Callback callbackPtr){
  registered_callback[comm] = callbackPtr;
}

bool CORGI85::addModule(CorgiModule *module) {
  this->moduleList[module->name()] = module;
  return true;
}

uint8_t CORGI85::loop(void)
{
  uint8_t received_command = run();
  if(received_command != 0 && registered_callback.count("received_command") > 0){
    Callback cb = registered_callback["received_command"];
    //(*cb)(123,(void *)"sssss");
    String a = "!23";
    String b = "456";
    std::vector<String> bbb;
    bbb.push_back(a);
    bbb.push_back(b);
    (*cb)(bbb);
  }
  return 1;
}



uint8_t CORGI85::run(void) //new data was recevied
{
  std::map<const char*, CorgiModule*>::iterator it = this->moduleList.begin();
  int i = 0;
  while (it != this->moduleList.end())
  {
      const char* word = it->first;
      CorgiModule *module = it->second;
      // Serial.printf("[%d] = %s\r\n", i, word);
      module->loop();
      i++;
      it++;
  }

  while (corgi_serial->available()) {
    String s = corgi_serial->readStringUntil('\n');
    if (s.indexOf("IFTTT,") != -1) {
      moduleList["IFTTT"]->cmd(s);
    }
    else if (s.indexOf("LINE,") != -1) {
      moduleList["LINE"]->cmd(s);
    }
  }

  return 0;

  while ((corgi_serial->available()) > 0 && (buffer_avaliable() < 255))
  {
    for (uint8_t index = 0; index < MAXLENGTH - 1; index++)
    {
      raw_buffer_ring[index] = raw_buffer_ring[index + 1];
    }
    raw_buffer_ring[MAXLENGTH - 1] = corgi_serial->read();

    uint8_t sumNum = checkSum(raw_buffer_ring, MAXLENGTH);

    if ((raw_buffer_ring[0] == 0xFF) && (raw_buffer_ring[1] == 0x17) && (raw_buffer_ring[2] == 0x04) && (raw_buffer_ring[MAXLENGTH - 1] == sumNum)) //head bit and sum are all right
    {
      receivedFlag = 1; //new data received
      return receivedFlag;
    }
    else
    {
      receivedFlag = 0; //data loss or error
      return receivedFlag;
    }
  }

  loop();

  return receivedFlag;
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

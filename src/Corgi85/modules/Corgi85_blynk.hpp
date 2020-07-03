
#ifndef CORGI_BLYNK_MODULE_H
#define CORGI_BLYNK_MODULE_H

#include "CorgiModule.h"
#include "StringSplitter.h" //https://github.com/aharshac/StringSplitter
#include "../Corgi85_blynk/corgi85_blynk.h"

CORGI85_BLINK corgi85_blynk;

class Corgi85_blynk : public CorgiModule
{
public:
  void setup(){

  };

  void loop()
  {
    if (corgi85_blynk.initial)
      Blynk.run();
  };

  void cmd(String cmd)
  {
    StringSplitter *splitter = new StringSplitter(cmd, ',', 4);

    if (splitter->getItemCount() >= 2)
    {

      String fn = String(splitter->getItemAtIndex(1));
      String v1 = String(splitter->getItemAtIndex(2));
      String v2 = String(splitter->getItemAtIndex(3));
      Serial.printf("fn = %s\r\nCMD=%s\t%s\r\n", fn.c_str(), v1.c_str(), v2.c_str());
      switch (fn.toInt())
      {
      case 0: // set auth
      {
        corgi85_blynk.auth = String(v1);
        Blynk.config(corgi85_blynk.auth.c_str());
        corgi85_blynk.initial = 1;
      }
      break;
      case 1: // set host
      {
        corgi85_blynk.host = String(v1);
      }
      break;
      case 2: // set port
      {
        corgi85_blynk.port = v1.toInt();
      }
      break;
      case 3: // write long
      {
        uint8_t vir_pin = v1.toInt();
        float value = v2.toInt();
        Blynk.virtualWrite(vir_pin, value);
      }
      break;
      case 4: // write float
      {
        uint8_t vir_pin = v1.toInt();
        float value = v2.toFloat();
        Blynk.virtualWrite(vir_pin, value);
      }
      break;
      case 5: // write char
      {
        uint8_t vir_pin = v1.toInt();
        Blynk.virtualWrite(vir_pin, v2.c_str());
      }
      break;
      case 6: // write noti
      {
        Blynk.notify(v1.c_str());
      }

      break;
      }
    }
    Serial.printf("MODULE = %s\r\nCMD=%s\r\n", this->name(), cmd.c_str());
  };

  const char *name()
  {
    return "BLYNK";
  };

protected:
private:
};

#endif

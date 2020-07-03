
#ifndef CORGI_THINGSPEAK_MODULE_H
#define CORGI_THINGSPEAK_MODULE_H

#include "CorgiModule.h"
#include "StringSplitter.h" //https://github.com/aharshac/StringSplitter
#include "../Corgi85_thingspeak/corgi85_thingspeak.h"

class CorgiThingSpeak : public CorgiModule
{
public:
  void setup(){
      // ts_init();
  };

  void loop(){

  };

  void cmd(String cmd)
  {
    Serial.printf("MODULE = %s\r\nCMD=%s\r\n", this->name(), cmd.c_str());

    ts_init();

    StringSplitter *splitter = new StringSplitter(cmd, ',', 4);
    int itemCount = splitter->getItemCount();

    if (itemCount == 3)
    {
      uint8_t fn = String(splitter->getItemAtIndex(1)).toInt();
      String first_field = String(splitter->getItemAtIndex(2));
      String second_field = String(splitter->getItemAtIndex(3));

      switch (fn)
      {
      case 0:
      {
        char *api_key;
        unsigned int size = 20;
        first_field.toCharArray(api_key, size);

        unsigned long channel_id = (unsigned long)second_field.toInt();

        ts_account(api_key, channel_id);
      }
      break;
      case 1:
      {
        ts_write_field((uint8_t)first_field.toInt(), (uint8_t)second_field.toInt());
      }
      break;

      default:
        break;
      }
    }
  };

  const char *name()
  {
    return "Thingspeak";
  };

protected:
private:
};

#endif

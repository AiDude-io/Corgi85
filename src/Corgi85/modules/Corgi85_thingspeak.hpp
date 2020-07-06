
#ifndef CORGI_THINGSPEAK_MODULE_H
#define CORGI_THINGSPEAK_MODULE_H

#include "CorgiModule.h"
#include "StringSplitter.h" //https://github.com/aharshac/StringSplitter
#include "../Corgi85_thingspeak/corgi85_thingspeak.h"

class CorgiThingSpeak : public CorgiModule
{
public:
  void
  setup(){

  };

  void loop(){

  };

  String strTrim(String data, char separator, int index)
  {
    int found = 0;
    int strIndex[] = {0, -1};
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++)
    {
      if (data.charAt(i) == separator || i == maxIndex)
      {
        found++;
        strIndex[0] = strIndex[1] + 1;
        strIndex[1] = (i == maxIndex) ? i + 1 : i;
      }
    }

    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
  };

  void cmd(String cmd)
  {
    Serial.printf("MODULE = %s\r\nCMD=%s\r\n", this->name(), cmd.c_str());

    cmd.trim();

    String fn = strTrim(cmd, ',', 1);

    if (fn == "init")
    {
      Serial.println(">>> process init ...");
      ts_init();
    }
    else if (fn == "account_setup")
    {
      Serial.println(">>> process account_setup ...");
      String cmd_api_key = strTrim(cmd, ',', 2);
      String cmd_channel_id = strTrim(cmd, ',', 3);

      int str_api_len = cmd_api_key.length() + 1;
      char buf_api_key[str_api_len];
      cmd_api_key.toCharArray(buf_api_key, str_api_len);
      unsigned long channel_id = (unsigned long)cmd_channel_id.toInt();

      Serial.print("api key : ");
      Serial.println(buf_api_key);
      Serial.print("channel id : ");
      Serial.println(channel_id);

      ts_account(buf_api_key, channel_id);
    }
    else if (fn == "write_field")
    {
      Serial.println(">>> process write_field ...");
      String cmd_field = strTrim(cmd, ',', 2);
      String cmd_value = strTrim(cmd, ',', 3);

      ts_write_field((uint8_t)cmd_field.toInt(), (uint8_t)cmd_value.toInt());
    }
  }

  const char *name()
  {
    return "Thingspeak";
  };

protected:
private:
};

#endif

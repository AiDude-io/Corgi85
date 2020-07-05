
#ifndef CORGI_LINE_MODULE_H
#define CORGI_LINE_MODULE_H

#include "CorgiModule.h"
#include <TridentTD_LineNotify.h> //https://github.com/TridentTD/TridentTD_LineNotify
#include "StringSplitter.h"
#include <ESP8266WiFi.h>
class CorgiLine : public CorgiModule
{
public:
  void setup(){};

  void loop(){};

  String getValue_from_string(String data, char separator, int index)
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
    String func = getValue_from_string(cmd, ',', 1);

    if (func == "setToken")
    {
      String setToken = getValue_from_string(cmd, ',', 2);
      LINE.setToken(setToken.c_str());
      Serial.println(setToken);
    }
    else if (func == "notify")
    {
      String notify = getValue_from_string(cmd, ',', 2);
      Serial.println(LINE.notify(notify.c_str()));
    }
    else if (func == "notifySticker")
    {
      int PackageIDn = getValue_from_string(cmd, ',', 2).toInt();
      int StickerIDn = getValue_from_string(cmd, ',', 3).toInt();
      Serial.println(LINE.notifySticker(PackageIDn, StickerIDn));
    }
    else if (func == "notifySticker_text")
    {
      String textn = getValue_from_string(cmd, ',', 2);
      int PackageIDn = getValue_from_string(cmd, ',', 3).toInt();
      int StickerIDn = getValue_from_string(cmd, ',', 4).toInt();
      Serial.println(LINE.notifySticker(textn.c_str(), PackageIDn, StickerIDn));
    }
    else if (func == "notifyPicture")
    {
      pic_notify = getValue_from_string(cmd, ',', 2);
    }
  };

  void raw(String s, uint16_t data_length)
  {
    size_t image_size = data_length;
    uint8_t *image_data = (uint8_t *)s.c_str();
    Serial.println(LINE.notifyPicture(pic_notify.c_str(), image_data, image_size));
  }

  const char *name()
  {
    return "LINE";
  };

protected:
private:
  String pic_notify = "";
};

#endif

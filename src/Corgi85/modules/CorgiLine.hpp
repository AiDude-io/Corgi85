
#ifndef CORGI_LINE_MODULE_H
#define CORGI_LINE_MODULE_H

#include "CorgiModule.h"
#include <TridentTD_LineNotify.h> //https://github.com/TridentTD/TridentTD_LineNotify
#include "StringSplitter.h"
#include <ESP8266WiFi.h>
class CorgiLine : public CorgiModule
{
public:
  String pic_notify = "";

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
    // Serial.printf("MODULE = %s\r\nCMD=%s\r\n", this->name(), cmd.c_str());
    // cmd.trim();
    // String func = getValue_from_string(cmd, ',', 1);

    StringSplitter *splitter = new StringSplitter(cmd, ',', 6);

    if (splitter->getItemCount() >= 2)
    {

      String func = String(splitter->getItemAtIndex(1));
      String v1 = String(splitter->getItemAtIndex(2));
      String v2 = String(splitter->getItemAtIndex(3));
      String v3 = String(splitter->getItemAtIndex(4));
      String v4 = String(splitter->getItemAtIndex(5));
      if (func == "setToken")
      {
        // String setToken = getValue_from_string(cmd, ',', 2);
        LINE.setToken(v1.c_str());
        Serial.println(v1.c_str());
      }
      else if (func == "notify")
      {
        // String notify = getValue_from_string(cmd, ',', 2);
        Serial.println(LINE.notify(v1.c_str()));
      }
      else if (func == "notifySticker")
      {
        // int PackageIDn = getValue_from_string(cmd, ',', 2).toInt();
        // int StickerIDn = getValue_from_string(cmd, ',', 3).toInt();
        Serial.println(LINE.notifySticker(v1.toInt(), v2.toInt()));
      }
      else if (func == "notifySticker_text")
      {
        // String textn = getValue_from_string(cmd, ',', 2);
        // int PackageIDn = getValue_from_string(cmd, ',', 3).toInt();
        // int StickerIDn = getValue_from_string(cmd, ',', 4).toInt();
        Serial.println(LINE.notifySticker(v1.c_str(), v2.toInt(), v3.toInt()));
      }
      else if (func == "notifyPicture")
      {
        // pic_notify = getValue_from_string(cmd, ',', 4);
        pic_notify = String(v4);
        LINE.notify(pic_notify.c_str());
      }
    }

    delete splitter;
  };

  void raw(const String& s, uint32_t data_length)
  {
    size_t image_size = data_length;
    uint8_t *image_data = (uint8_t *)s.c_str();
    LINE.notify(String(data_length).c_str());
    Serial.println(LINE.notifyPicture(pic_notify.c_str(), image_data, image_size));
  };

  const char *name()
  {
    return "LINE";
  };

protected:
private:
};

#endif


#ifndef CORGI_LINE_MODULE_H
#define CORGI_LINE_MODULE_H

#include "CorgiModule.h"
#include <TridentTD_LineNotify.h>
#include "StringSplitter.h"
#include <ESP8266WiFi.h> 
class CorgiLine : public CorgiModule {
  public:
    void setup() {};

    void loop() {
    };
    String getValuetong(String data, char separator, int index)
    {
      int found = 0;
      int strIndex[] = {0, -1};
      int maxIndex = data.length() - 1;

      for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
          found++;
          strIndex[0] = strIndex[1] + 1;
          strIndex[1] = (i == maxIndex) ? i + 1 : i;
        }
      }

      return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
    };
    void cmd(String cmd) {
      Serial.printf("MODULE = %s\r\nCMD=%s\r\n", this->name(), cmd.c_str() );
      cmd.trim();
      String func = getValuetong(cmd,',',1);
      if(func == "setToken"){
        String setToken = getValuetong(cmd,',',2);
        LINE.setToken(setToken);
        Serial.println(setToken);
      }else if (func == "notify"){
        String notify = getValuetong(cmd,',',2);
        Serial.println(LINE.notify(notify));
      }else if (func == "notifySticker"){
        int PackageIDn = getValuetong(cmd,',',2).toInt();
        int StickerIDn = getValuetong(cmd,',',3).toInt();
        Serial.println(LINE.notifySticker(PackageIDn,StickerIDn));
      }else if (func == "notifySticker_text"){
        String textn = getValuetong(cmd,',',2);
        int PackageIDn = getValuetong(cmd,',',3).toInt();
        int StickerIDn = getValuetong(cmd,',',4).toInt();
        Serial.println(LINE.notifySticker(textn,PackageIDn,StickerIDn));
      }else if (func == "notifyPicture"){
        
        // Serial.println(LINE.notifyPicture());
      }

    };

    const char* name() {
      return "LINE";
    };
  protected:
  private:
};

#endif

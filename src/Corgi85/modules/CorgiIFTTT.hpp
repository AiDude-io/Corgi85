
#ifndef CORGI_IFTT_MODULE_H
#define CORGI_IFTT_MODULE_H

#include "CorgiModule.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <StringSplitter.h>


class CorgiIFTTT : public CorgiModule {
  public:
    void setup() {};
    void loop() {
    };

    void cmd(String cmd) {
      StringSplitter *splitter = new StringSplitter(cmd, ',', 6); 
      if (splitter->getItemCount() >= 2) {

        String func = String(splitter->getItemAtIndex(1));
        String v1 = String(splitter->getItemAtIndex(2));
        String v2 = String(splitter->getItemAtIndex(3));
        String v3 = String(splitter->getItemAtIndex(4));
        String v4 = String(splitter->getItemAtIndex(5));      
        if (func == "fire") {
          Serial.println("fire!");
          Serial.println(v1);
          HTTPClient http; 
          http.begin(v1); //Specify the URL
          int httpCode = http.GET();
      
          if (httpCode > 0) { //Check for the returning code
      
              String payload = http.getString();
              Serial.println(httpCode);
              Serial.println(payload);
            }
      
          else {
            Serial.println("Error on HTTP request");
          }
      
          http.end(); //Free the resources          
        }
      };
      delete splitter;
    }


    const char* name() {
      return "IFTTT";
    };
  protected:
  private:
};

#endif

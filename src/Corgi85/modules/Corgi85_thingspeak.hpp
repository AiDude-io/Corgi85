
#ifndef CORGI_THINGSPEAK_MODULE_H
#define CORGI_THINGSPEAK_MODULE_H

#include "CorgiModule.h"

class CorgiThingSpeak : public CorgiModule
{
public:
  void setup(){};

  void loop(){};

  void cmd(String cmd)
  {
    Serial.printf("MODULE = %s\r\nCMD=%s\r\n", this->name(), cmd.c_str());
  };

  const char *name()
  {
    return "THINGSPEAK";
  };

protected:
private:
};

#endif

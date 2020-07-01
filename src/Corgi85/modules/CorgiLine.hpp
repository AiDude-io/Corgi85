
#ifndef CORGI_LINE_MODULE_H
#define CORGI_LINE_MODULE_H

#include "CorgiModule.h"


class CorgiLine : public CorgiModule {
  public:
    void setup() {};

    void loop() {
    };

    void cmd(String cmd) {
      Serial.printf("MODULE = %s\r\nCMD=%s\r\n", this->name(), cmd.c_str() );
    };

    const char* name() {
      return "LINE";
    };
  protected:
  private:
};

#endif

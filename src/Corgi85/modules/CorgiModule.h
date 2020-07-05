#ifndef CorgiModule_H
#define CorgiModule_H

#include <Arduino.h>

class CorgiModule
{
protected:
public:
  virtual void setup() = 0;
  virtual void loop() = 0;
  virtual const char *name() = 0;
  virtual void cmd(String s) = 0;
  virtual void raw(String s, uint16_t data_length)
  {
  }
};

#endif

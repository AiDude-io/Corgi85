#include <Arduino.h>
#include "corgi85_utility.h"
#include "modules/CorgiIFTTT.hpp"
#include "modules/CorgiLine.hpp"
#include <vector>

CORGI85 corgi85(&Serial);
void DoBlynk(std::vector<String> data)
{
  String a = data[0];
  //String x = String(static_cast<char *>(args));
}

void setup() {
  delay(2000);
  Serial.begin(115200);
  corgi85.registerCallback("BLYNK_BEGIN",&DoBlynk);
  corgi85.addModule(new CorgiIFTTT());
  corgi85.addModule(new CorgiLine());
}

void loop() {
  corgi85.run();
  // corgi85.printModulesList();
  delay(100);
}

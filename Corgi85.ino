#include "corgi85_utility.h"
#include <vector>
#include "line.h"

CORGI85 corgi85(&Serial);

void DoBlynk(std::vector<String> data)
{
  
//  String a = data[0];
  //String x = String(static_cast<char *>(args));
}
void setup() {
  delay(2000);
  Serial.begin(115200);
  corgi85.registerCallback("BLYNK_BEGIN",&DoBlynk);
  corgi85.registerCallback("LINE_BEGIN",&DoLINE);
}

void loop() {
  corgi85.run();
  delay(100);
}

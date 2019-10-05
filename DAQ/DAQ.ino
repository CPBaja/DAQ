#include <Arduino.h>

#include "Buffer.h"
#include "AtomicFrame.h"

Buffer buf0 = *new Buffer();

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  buf0.Append(100, millis());
  Serial.print(buf0._headIndex);
  Serial.print(" ");
  Serial.println(buf0.GetTime(i));
  delay(10);
}

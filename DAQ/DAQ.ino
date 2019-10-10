#include <Arduino.h>

#include "Buffer.h"
#include "AtomicBuffer.h"

Buffer buf0('A');
Buffer buf1('B');
Buffer buf2('C');
Buffer buf3('D');
Buffer buf4('E');
Buffer buf5('F');
Buffer buf6('G');
Buffer buf7('H');
Buffer buf8('I');
Buffer buf9('J');
Buffer buf10('K');

AtomicBuffer abuf0('Z');
AtomicBuffer abuf1('Y');
AtomicBuffer abuf2('X');
AtomicBuffer abuf3('W');

const int chipSelect = BUILTIN_SDCARD;

void setup()
{
  Serial.begin(9600);
  SD.begin(chipSelect);

  delay(1000);
  // Delay to allow the Serial and SD to setup. Probably not needed?
}

void loop()
{
  int head = buf0.GetSize();
  if(head < buf0.GetMaxSize())
  {
    buf0.Append(100, micros());
  }
  else
  {
    buf0.ClearBuffer();
    Serial.print("Swap ");
    Serial.print(i);
    Serial.print(" ");
    Serial.println(micros());
    i++;
  }

}

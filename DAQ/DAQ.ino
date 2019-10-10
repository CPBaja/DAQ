#include <Arduino.h>
#include <SD.h>

#include "Buffer.h"
#include "AtomicBuffer.h"
#include "Sensor.h"
int i = 0;
File file;

Sensor sens0(14, 'A');
Sensor sens1(14, 'A');
Sensor sens2(14, 'A');
Sensor sens3(14, 'A');
Sensor sens4(14, 'A');
Sensor sens5(14, 'A');
Sensor sens6(14, 'A');
Sensor sens7(14, 'A');
Sensor sens8(14, 'A');
Sensor sens9(14, 'A');
Sensor sens10(14, 'A');
Sensor sens11(14, 'A');
Sensor sens12(14, 'A');
Sensor sens13(14, 'A');
Sensor sens14(14, 'A');
Buffer buf0;

const int chipSelect = BUILTIN_SDCARD;

void setup()
{
  Serial.begin(9600);
  SD.begin(chipSelect);
  buf0.SetIdentifier('A');


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
    buf0.WriteBufferToSD(file, "test3.txt");
    buf0.ClearBuffer();
  }

}

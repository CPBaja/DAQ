#include <Arduino.h>

#include "Buffer.h"
#include "AtomicBuffer.h"

const int maxSize = 100;

Buffer buf0(maxSize, 'A');
Buffer buf1(maxSize, 'B');
Buffer buf2(maxSize, 'C');
Buffer buf3(maxSize, 'D');
Buffer buf4(maxSize, 'E');
Buffer buf5(maxSize, 'F');
Buffer buf6(maxSize, 'G');
Buffer buf7(maxSize, 'H');
Buffer buf8(maxSize, 'I');
Buffer buf9(maxSize, 'J');
Buffer buf10(maxSize, 'K');

AtomicBuffer abuf0(maxSize, 'Z');
AtomicBuffer abuf1(maxSize, 'Y');
AtomicBuffer abuf2(maxSize, 'X');
AtomicBuffer abuf3(maxSize, 'W');

int i = 0;
unsigned long startTime;
unsigned long resultTime;

void setup()
{
  Serial.begin(9600);

  while(Serial.available() == 0)
  {
    
  }
}

void loop()
{
  int head = abuf0.GetSize();
  if(head < maxSize)
  {
    abuf0.Append(100, micros());
  }
  else
  {
    abuf0.Swap();
    Serial.print("Swap ");
    Serial.print(i);
    Serial.print(" ");
    Serial.println(micros());
    i++;
  }

}

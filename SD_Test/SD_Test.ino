#include <SD.h>

const String DATA = "F";

File file;

void writeToSD(String fileName, int dataWriteSize)
{
    file = SD.open(fileName, O_CREAT | O_WRITE);
    
    for(int i = 0;i < dataWriteSize - 1;i++)
    {
        file.print(DATA);
    }
    file.print('\n');
    
    file.flush();
    file.close();
}

void serialFlush()
{
  while(Serial.available() > 0)
  {
    char t = Serial.read();
  }
}  

void setup()
{
     Serial.begin(9600);
     Serial.setTimeout(1000);
     SD.begin(BUILTIN_SDCARD);
     
     // Allow serial port to setup.
     delay(1000);

}

void loop()
{
    while(Serial.available() > 0)
    {
      String fileName = "test0.txt";
      // The SD library writes data in 512 byte blocks.
      // Setting the DATA_WRITE_SIZE larger than 512 may cause the buffer to be overwritten.
      int dataWriteSize = Serial.parseInt();
      
      unsigned long start = micros();
  
      writeToSD(fileName, dataWriteSize);
      
      unsigned long resultTime = micros() - start;

      Serial.println(resultTime);

      delay(1);
      serialFlush();
    }
}
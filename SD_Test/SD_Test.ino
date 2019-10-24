#include <SD.h>

const int DATA = 1023;

File file;

void writeToSD(String fileName, int dataWriteSize)
{
    char __dataFileName[sizeof(fileName)];
    fileName.toCharArray(__dataFileName, sizeof(__dataFileName));
    file = SD.open(__dataFileName, FILE_WRITE);
    
    for(int i = 0;i < dataWriteSize;i++)
    {
        file.write((byte*)&DATA, sizeof(int));
    }
    
    file.flush();
    file.close();
}

void serialFlush()
{
  while(Serial.available() > 0)
  {
    Serial.read();
  }
}  

void setup()
{
     Serial.begin(9600);
     Serial.setTimeout(1000);
     SD.begin(BUILTIN_SDCARD);
     
    while(!Serial)
    {
        ; // Wait for serial port to connect. Needed for native USB port only.
    }

}

void loop()
{
    while(Serial.available() > 0)
    {
      String fileName = "sd_test2.bin";
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

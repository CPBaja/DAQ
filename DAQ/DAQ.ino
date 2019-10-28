#include <Arduino.h>
#include <SD.h>

#include "Buffer.h"
#include "Sensor.h"

/* Sensor Parameters */
// If you want to read as fast as possible, set timeDelay to 0.
const int readingsPerSecond = 100;
const int timeDelay = 0;//int(1000000 / readingsPerSecond * 1);
Sensor sens0(14, timeDelay);
Sensor sens1(15, timeDelay);
Sensor sens2(16, timeDelay);
Sensor sens3(17, timeDelay);
Sensor sens4(18, timeDelay);
Sensor sens5(19, timeDelay);
Sensor sens6(20, timeDelay);
Sensor sens7(21, timeDelay);
Sensor sens8(22, timeDelay);
Sensor sens9(23, timeDelay);
unsigned long readingStartTime;

const int sensorCount = 9;
Sensor * allSensors[sensorCount] = {&sens0, &sens1, &sens2, &sens4, &sens5, &sens6, &sens7, &sens8, &sens9};

/* SD Card Parameters */
const int chipSelect = BUILTIN_SDCARD;
unsigned long fileNameChangeTime;
const unsigned long fileNameChangeInterval = 1000000;
int fileNameCounter = 0;
String saveFileName = "Beta_0.bin";

/* General I/O Parameters */
const bool writeToFile = true;
const bool writeToSerial = true;

void setup()
{
    Serial.begin(9600);
    SD.begin(chipSelect);

    /*while(!Serial)
    {
        ; // Wait for serial port to connect. Needed for native USB port only.
    }*/
    
    fileNameChangeTime = micros();
    readingStartTime = micros();
}

void loop()
{
    // Checks each sensor to see if they're ready to read.
    // If the sensor is ready to read, it'll read.
    for(int i = 0;i < sensorCount;i++)
    {
        if(allSensors[i]->ReadyToRead())
        {
            allSensors[i]->ReadSensor();
        }
    }

    if(allSensors[0]->IsFull())
    {
        if(writeToFile)
        {
            writeSensorsToFile();
        }
        if(writeToSerial)
        {
            writeSensorsToSerial();
        }

        for(int i = 0;i < sensorCount;i++)
        {
            allSensors[i]->ClearSensor();
        }
        readingStartTime = micros();
    }
}

void writeSensorsToFile()
{
    char __dataFileName[sizeof(saveFileName)];
    saveFileName.toCharArray(__dataFileName, sizeof(__dataFileName));
    File file = SD.open(__dataFileName, FILE_WRITE);
    
    unsigned long readingEndTime = micros();
    
    file.write((byte*)&readingStartTime, sizeof(unsigned long));
    
    for(int i = 0;i < sensorCount;i++)
    {
        allSensors[i]->WriteSensorToSD(&file);
    }
    
    file.write((byte*)&readingEndTime, sizeof(unsigned long));
    
    file.close();
}

void writeSensorsToSerial()
{
    Serial.println(readingStartTime);
    for(int i = 0;i < sensorCount;i++)
    {
        allSensors[i]->PrintSensor();
    }
    Serial.println(micros());
}

void updateFileName()
{
    if(micros() - fileNameChangeTime > fileNameChangeInterval)
    {
        fileNameCounter++;
        saveFileName = String(fileNameCounter) + ".bin";
        fileNameChangeTime = micros();
    }
}

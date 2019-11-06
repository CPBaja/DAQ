#include <Arduino.h>
#include <SD.h>

#include "Buffer.h"
#include "Sensor.h"

/* Sensor Parameters */
// If you want to read as fast as possible, set readingDelay to 0.
const int readingsPerSecond = 1000;
const int readingDelay = int(1000000 / readingsPerSecond * 1);
Sensor sens0(14, readingDelay);
Sensor sens1(15, readingDelay);
Sensor sens2(16, readingDelay);
Sensor sens3(17, readingDelay);
Sensor sens4(18, readingDelay);
Sensor sens5(19, readingDelay);
Sensor sens6(20, readingDelay);
Sensor sens7(21, readingDelay);
Sensor sens8(22, readingDelay);
Sensor sens9(23, readingDelay);
unsigned long readingStartTime;

const int sensorCount = 9;
Sensor * allSensors[sensorCount] = {&sens0, &sens1, &sens2, &sens4, &sens5, &sens6, &sens7, &sens8, &sens9};

/* SD Card Parameters */
const int chipSelect = BUILTIN_SDCARD;
unsigned long fileNameChangeTime;
const unsigned long fileNameChangeInterval = 1000000;
int fileNameCounter = 0;
String saveFileName = "test9.bin";

/* XBee Parameters */
const int broadcastsPerSecond = 10;
const int broadcastDelay = int(1000000 / broadcastsPerSecond);
unsigned long broadcastStartTime;

/* General I/O Parameters */
const bool writeToFile = true;
const bool writeToSerial = false;
const bool xbeeBroadcast = false;
int lastReaings[sensorCount];

void setup()
{
    Serial.begin(9600);
    SD.begin(chipSelect);
    
    fileNameChangeTime = micros();
    readingStartTime = micros();
    broadcastStartTime = micros();
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

    if(xbeeBroadcast)
    {
        if(abs(micros() - broadcastStartTime > broadcastDelay))
        {
            Serial.print(micros());
            for(int i = 0;i < sensorCount;i++)
            {
                Serial.print(";");
                Serial.print(allSensors[i]->GetPin());
                Serial.print(";");
                Serial.print(allSensors[i]->GetLastReading());
            }
            Serial.println();

            broadcastStartTime = micros();
        }
    }
    
}

void writeSensorsToFile()
{
    char __dataFileName[sizeof(saveFileName)];
    saveFileName.toCharArray(__dataFileName, sizeof(__dataFileName));
    File file = SD.open(__dataFileName, FILE_WRITE);
    
    unsigned long readingEndTime = micros();
    
    file.write((byte*)&readingStartTime, sizeof(unsigned long));

    file.flush();
    
    for(int i = 0;i < sensorCount;i++)
    {
        allSensors[i]->WriteSensorToSD(&file);
    }
    
    file.write((byte*)&readingEndTime, sizeof(unsigned long));

    file.flush();
    
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

#include <Arduino.h>
#include <SD.h>

#include "Buffer.h"
#include "AtomicBuffer.h"
#include "Sensor.h"

/* Sensor Parameters */
// If you want to read as fast as possible, set timeDelay to 0.
const int readingsPerSecond = 1000;
// int(1000000 / readingsPerSecond * 0.95) is the formula.
// 0.95 relates to the the timing precision, i.e. within 95% of the interval.
const int timeDelay = int(1000000 / readingsPerSecond * 1);
Sensor sens0(14, 'A', timeDelay);
Sensor sens1(15, 'B', timeDelay);
Sensor sens2(16, 'C', timeDelay);
Sensor sens3(17, 'D', timeDelay);
Sensor sens4(18, 'E', timeDelay);
Sensor sens5(19, 'F', timeDelay);
Sensor sens6(20, 'G', timeDelay);
Sensor sens7(21, 'H', timeDelay);
Sensor sens8(22, 'I', timeDelay);
Sensor sens9(23, 'J', timeDelay);

const int sensorCount = 10;
Sensor * allSensors[sensorCount] = {&sens0, &sens1, &sens2, &sens3, &sens4, &sens5, &sens6, &sens7, &sens8, &sens9};

/* SD Card Parameters */
const int chipSelect = BUILTIN_SDCARD;
unsigned long fileNameChangeTime;
const unsigned long fileNameChangeInterval = 1000000;
int fileNameCounter = 0;
String saveFileName = "0.txt";

void setup()
{
    Serial.begin(9600);
    SD.begin(chipSelect);

    while(!Serial)
    {
        ; // Wait for serial port to connect. Needed for native USB port only.
    }
    
    fileNameChangeTime = micros();
}

void loop()
{
    // Checks each sensor to see if they're ready to read.
    // Could be slightly faster if we know every sensor has the same interval.
    // If the sensor is ready to read, it'll read.
    for(int i = 0;i < sensorCount;i++)
    {
        if(allSensors[i]->ReadyToRead())
        {
            allSensors[i]->ReadSensor();
        }

        // One reading for every sensor will be slightly delayed when we output data.
        if(allSensors[i]->IsFull())
        {
            allSensors[i]->PrintSensor();
            allSensors[i]->WriteSensorToSD(saveFileName);
            allSensors[i]->ClearSensor();
        }
    }
}

void updateFileName()
{
    if(micros() - fileNameChangeTime > fileNameChangeInterval)
    {
        fileNameCounter++;
        saveFileName = String(fileNameCounter) + ".txt";
        fileNameChangeTime = micros();
    }
}

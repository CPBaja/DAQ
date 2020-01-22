#include <Arduino.h>
#include <SD.h>
#include <Bounce2.h>

#include "Buffer.h"
#include "Sensor.h"

/* Sensor Parameters */
// If you want to read as fast as possible, set readingDelay to 0.
const int readingsPerSecond = 1000;
const int readingDelay = int(1000000 / readingsPerSecond);
Sensor frPot(14, readingDelay);
Sensor brPot(15, readingDelay);
Sensor sPot(16, readingDelay);
Sensor fx(17, readingDelay);
Sensor fy(18, readingDelay);
Sensor fz(19, readingDelay);
Sensor mx(20, readingDelay);
Sensor my(21, readingDelay);
Sensor mz(22, readingDelay);
Sensor pos(23, readingDelay);
unsigned long readingStartTime;

const int sensorCount = 10;
Sensor * allSensors[sensorCount] = {&frPot, &brPot, &sPot, &fx, &fy, &fz, &mx, &my, &mz, &pos};

/* SD Card Parameters */
const int chipSelect = BUILTIN_SDCARD;
unsigned long fileNameChangeTime;
const unsigned long fileNameChangeInterval = 0;
int fileNameCounter = 0;
String saveFileName = "0.bin";

/* XBee Parameters */
const int broadcastsPerSecond = 10;
const int broadcastDelay = int(1000000 / broadcastsPerSecond);
unsigned long broadcastStartTime;

/* General I/O Parameters */
const bool writeToFile = true;
const bool writeToSerial = false;
const bool xbeeBroadcast = true;
int lastReaings[sensorCount];

/* Button Bouncing */
Bounce debouncer = Bounce();
const int button_pin = 2;
const int led_pin = 4;
const int button_time = 100;
int ledState = LOW;

void setup()
{
    Serial.begin(9600);
    SD.begin(chipSelect);

    delay(1000);
    
    pinMode(button_pin,INPUT_PULLDOWN);
    debouncer.attach(button_pin);
    debouncer.interval(button_time);
    
    pinMode(led_pin,OUTPUT);
    digitalWrite(led_pin,ledState);
    
    fileNameChangeTime = micros();
    readingStartTime = micros();
    broadcastStartTime = micros();

    char __dataFileName[sizeof(saveFileName)];
    saveFileName.toCharArray(__dataFileName, sizeof(__dataFileName));
    while(true)
    {
        char __dataFileName[sizeof(saveFileName)];
        saveFileName.toCharArray(__dataFileName, sizeof(__dataFileName));
        if(SD.exists(__dataFileName))
        {
            updateFileName();
        }
        else
        {
            break;
        }
    }
}

void loop()
{
    // Update the debouncer
    debouncer.update();
    if(debouncer.fell())
    {
        if(ledState == LOW)
        {
            ledState = HIGH;
        }
        else
        {
            ledState = LOW
        }
        digitalWrite(led_pin,ledState);
    }
    
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
            for(int i = 3;i < sensorCount;i++)
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

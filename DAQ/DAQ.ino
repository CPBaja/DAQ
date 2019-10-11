#include <Arduino.h>
#include <SD.h>

#include "Buffer.h"
#include "AtomicBuffer.h"
#include "Sensor.h"
int i = 0;

int timeDelay = 9500;
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

const int chipSelect = BUILTIN_SDCARD;

unsigned long startTime;
String saveFileName = "4.txt";

File file;

void setup()
{
    Serial.begin(9600);
    SD.begin(chipSelect);
  
    delay(1000);
    // Delay to allow the Serial and SD to setup. Probably not needed?


    startTime = micros();
}

void loop()
{

    // They're all the same size buffer, so we only need to check one.
    if(sens0.ReadyToRead())
    {
        sens0.ReadSensor();
        sens1.ReadSensor();
        sens2.ReadSensor();
        sens3.ReadSensor();
        sens4.ReadSensor();
        sens5.ReadSensor();
        sens6.ReadSensor();
        sens7.ReadSensor();
        sens8.ReadSensor();
        sens9.ReadSensor();
    }
  
    if(sens0.IsFull())
    {
        unsigned long printTime = micros();
        sens0.PrintSensor();
        //sens0.WriteSensorToSD(saveFileName);
        sens0.ClearSensor();
        sens1.PrintSensor();
        //sens1.WriteSensorToSD(saveFileName);
        sens1.ClearSensor();
        sens2.PrintSensor();
        //sens2.WriteSensorToSD(saveFileName);
        sens2.ClearSensor();
        sens3.PrintSensor();
        //sens3.WriteSensorToSD(saveFileName);
        sens3.ClearSensor();
        sens4.PrintSensor();
        //sens4.WriteSensorToSD(saveFileName);
        sens4.ClearSensor();
        sens5.PrintSensor();
        //sens5.WriteSensorToSD(saveFileName);
        sens5.ClearSensor();
        sens6.PrintSensor();
        //sens6.WriteSensorToSD(saveFileName);
        sens6.ClearSensor();
        sens7.PrintSensor();
        //sens7.WriteSensorToSD(saveFileName);
        sens7.ClearSensor();
        sens8.PrintSensor();
        //sens8.WriteSensorToSD(saveFileName);
        sens8.ClearSensor();
        sens9.PrintSensor();
        //sens9.WriteSensorToSD(saveFileName);
        sens9.ClearSensor();
        unsigned long endTime = micros() - startTime;
        //Serial.println(endTime);
        endTime = micros() - printTime;
        //Serial.println(endTime);
        startTime = micros();
    }
}

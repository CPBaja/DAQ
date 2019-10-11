#ifndef BUFFER_H
#define BUFFER_H

#include <Arduino.h>
#include <SD.h>

#include "Buffer.h"

const int _maxSize = 100;

class Buffer  
{

    public:
        Buffer();
        void SetIdentifier(char identifier);
        int Append(int value, unsigned long timestamp);
        int GetValue(int index);
        unsigned long GetTime(int index);
        int GetSize();
        int GetMaxSize();
        void PrintBuffer();
        void WriteBufferToSD(String fileName);
        void ClearBuffer();
     
    private:
        char _identifier;
        int _dataBuf[_maxSize];
        unsigned long _timeBuf[_maxSize];
        int _headIndex;
};

#endif

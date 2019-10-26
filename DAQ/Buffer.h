#ifndef BUFFER_H
#define BUFFER_H

#include <Arduino.h>
#include <SD.h>

#include "Buffer.h"

const int _maxSize = 1000;

class Buffer  
{

    public:
        Buffer();
        void SetIdentifier(char identifier);
        int Append(int value);
        int GetValue(int index);
        int GetSize();
        int GetMaxSize();
        void PrintBuffer();
        void WriteBufferToSD(File * file);
        void ClearBuffer();
     
    private:
        char _identifier;
        short int _dataBuf[_maxSize];
        int _headIndex;
};

#endif

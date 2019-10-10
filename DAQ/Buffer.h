#ifndef BUFFER_H
#define BUFFER_H

#include "Buffer.h"

class Buffer  
{

    public:
        Buffer(int maxSize, char identifier);
        int Append(int value, unsigned long timestamp);
        int GetValue(int index);
        unsigned long GetTime(int index);
        int GetSize();
        void PrintBuffer();
        void ClearBuffer();
     
    private:
        char _identifier;
        int * _dataBuf;
        unsigned long * _timeBuf;
        int _headIndex;
        int _maxSize;
};

#endif
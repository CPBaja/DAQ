#ifndef BUFFER_H
#define BUFFER_H

#include "Buffer.h"

class Buffer  
{

    public:
        Buffer(int maxByteSize);
        void Append(int value, unsigned long timestamp);
        void ClearBuffer();

        int GetValue(int index);
        unsigned long GetTime(int index);
     
    private:
        int * _dataBuf;
        unsigned long * _timeBuf;
        int _headIndex;
        int _maxSize;
};

#endif

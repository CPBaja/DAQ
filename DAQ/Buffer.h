#ifndef BUFFER_H
#define BUFFER_H

#include "Buffer.h"

const int MAX_BUFFER_SIZE = 200;

class Buffer  
{

    public:
        Buffer();
        int GetSizeInBytes();
        void Append(int value, unsigned long timestamp);
        void ClearBuffer();
        int GetValue(int index);
        unsigned long GetTime(int index);
        long _headIndex;
     
    private:
        int _dataBuf[MAX_BUFFER_SIZE];
        unsigned long _timeBuf[MAX_BUFFER_SIZE];

};

#endif

#ifndef ATOMICBUFFER_H
#define ATOMICBUFFER_H

#include "Buffer.h"

class AtomicBuffer
{

    public:
        AtomicBuffer(char identifier);
        int Append(int value, unsigned long timestamp);
        int GetValue(int index);
        unsigned long GetTime(int index);
        int GetSize();
        void PrintBuffer();
        void ClearBuffer();

    private:
        void Swap();
        char _identifier;
        unsigned char _currentBuffer;
        Buffer * _primaryBuffer;
        Buffer * _secondaryBuffer;
};

#endif

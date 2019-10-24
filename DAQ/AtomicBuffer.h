#ifndef ATOMICBUFFER_H
#define ATOMICBUFFER_H

#include "Buffer.h"

class AtomicBuffer
{

    public:
        AtomicBuffer();
        void SetIdentifier(char identifier);
        int Append(int value, unsigned long timestamp);
        int GetValue(int index);
        int GetSize();
        void PrintBuffer();
        void WriteBufferToSD(String fileName);
        void ClearBuffer();

    private:
        void Swap();
        unsigned char _currentBuffer;
        Buffer _primaryBuffer;
        Buffer _secondaryBuffer;
};

#endif

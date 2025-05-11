#ifndef IReader_H
#define IReader_H

#include "String.h"

class IReader
{
public:
    virtual String* ReadLine() = 0;
};

#endif
#ifndef IReader_H
#define IReader_H

#include "String.h"

/// <summary>
/// Интерфейс определящ поведението на потребителският вход
/// </summary>

class IReader
{
public:
    virtual String* ReadLine() = 0;
};

#endif
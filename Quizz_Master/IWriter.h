#ifndef IWriter_H 
#define IWriter_H

#include "String.h"

/// <summary>
/// Интерфейс определящ поведението на потребителският изход
/// </summary>

class IWriter
{
public:
    virtual void Write(const String& str) = 0;
    virtual void WriteLine(const String& str) = 0;
};

#endif
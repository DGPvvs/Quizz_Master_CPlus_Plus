#ifndef IReader_H
#define IReader_H

#include "String.h"

/// <summary>
/// ��������� ��������� ����������� �� ��������������� ����
/// </summary>

class IReader
{
public:
    virtual String* ReadLine() = 0;
};

#endif
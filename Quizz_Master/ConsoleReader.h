#ifndef ConsoleReader_H
#define ConsoleReader_H

#include "IReader.h"

/// <summary>
/// ���� ������������� ���� �� ���������
/// </summary>

class ConsoleReader : public IReader
{
public:
    virtual String* ReadLine() override;
};

#endif
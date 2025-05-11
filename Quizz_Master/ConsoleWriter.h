#ifndef ConsoleWriter_H
#define ConsoleWriter_H

#include "IWriter.h"

class ConsoleWriter : public IWriter
{
public:
    virtual void Write(const String& str) override;
    virtual void WriteLine(const String& str) override;
};

#endif
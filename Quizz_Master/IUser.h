#ifndef IUser_H
#define IUser_H

#include "CommandStruct.h"
#include "IWriter.h"
#include "IReader.h"

class IUser
{
public:
    virtual String getName() const = 0;
    virtual String getUserName() const = 0;
    virtual void Login() = 0;
    virtual void Logout() = 0;
    virtual void Action(const CommandStruct&) = 0;
    virtual IWriter& Writer() = 0;
    virtual IReader& Reader() = 0;
    virtual void Print() = 0;
    virtual bool GetIsHasLog() = 0;
    virtual String BuildUserData() = 0;
    virtual void Help() = 0;
    virtual unsigned int Hash(const String& str) = 0;
    virtual void SetIsHasLog(bool) = 0;
};

#endif
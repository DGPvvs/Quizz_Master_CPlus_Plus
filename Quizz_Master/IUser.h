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
    virtual void UserLoop(const CommandStruct&) = 0;
    virtual IWriter& Writer() = 0;
    virtual IReader& Reader() = 0;
    virtual void Print() = 0;
    virtual bool GetIsHasLog() = 0;
    virtual String BuildUserData() = 0;
};

#endif
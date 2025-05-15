#ifndef IUser_H
#define IUser_H

#include "CommandStruct.h"
#include "IWriter.h"
#include "IReader.h"
#include "UserStruct.h"

class IUser
{
public:
    virtual String getName() const = 0;
    virtual void setFirstName(const String) = 0;
    virtual void setLastName(const String) = 0;
    virtual String getUserName() const = 0;
    virtual void setUserName(const String) = 0;
    virtual void setId(const unsigned int) = 0;
    virtual unsigned int getId() const = 0;
    virtual String getFileName() const = 0;
    virtual void setFileName(const String) = 0;
    virtual void Login() = 0;
    virtual void Logout() = 0;
    virtual void Action(const CommandStruct&) = 0;
    virtual IWriter& Writer() = 0;
    virtual IReader& Reader() = 0;
    virtual void Print() = 0;
    virtual bool GetIsHasLog() = 0;
    virtual String BuildUserData() = 0;
    virtual void Help() = 0;
    virtual unsigned int Hash(const String&) = 0;
    virtual void SetIsHasLog(bool) = 0;
    virtual int FindUserData(UserStruct&, bool) = 0;
    virtual void AllUsers(String&) = 0;
};

#endif
#ifndef User_H
#define User_H

#include "IUser.h"
#include "String.h"
#include "IWriter.h"
#include "IReader.h"
#include "CommandStruct.h"

class User : public IUser
{
private:
    unsigned int id;

    String firstName;
    String lastName;
    String userName;

    unsigned int password;

    bool isHasLogin;

    IWriter* writer;
    IReader* reader;

protected:
    void SetIsHasLog(bool);

    unsigned int GetPassword() const;
    void SetPassword(unsigned int);

    unsigned int Hash(const String& str);

public:
    User(IWriter* writer, IReader* reader);
    virtual String getName() const override;
    virtual String getUserName() const override;

    virtual void Login() override;
    virtual void Logout() override;
    virtual void UserLoop(const CommandStruct&) override;
    virtual IWriter& Writer() override;
    virtual IReader& Reader() override;
    virtual bool GetIsHasLog() override;

    virtual void Print() override;
    virtual String BuildUserData() override;

    virtual ~User() {}
};

#endif
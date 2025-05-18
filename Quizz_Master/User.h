#ifndef User_H
#define User_H

#include "IUser.h"
#include "String.h"
#include "IWriter.h"
#include "IReader.h"
#include "IBaseProvider.h"
#include "CommandStruct.h"
#include "UserStruct.h"

class User : public IUser
{
private:
    unsigned int id;

    String firstName;
    String lastName;
    String userName;
    String fileName;

    unsigned int password;

    bool isHasLogin;

    IWriter* writer;
    IReader* reader;
    IBaseProvider* provider;    

protected:
    void SetIsHasLog(bool);

    unsigned int GetPassword() const;
    void SetPassword(unsigned int); 
    virtual IWriter& Writer() override;
    virtual IReader& Reader() override;
    virtual IBaseProvider& Provider() override;
    int FindUserIndex(UserStruct& us, Vector<String>& usersVec);

public:
    User(IWriter*, IReader*, IBaseProvider*);
    virtual String getName() const override;
    virtual void setFirstName(const String) override;
    virtual void setLastName(const String) override;

    virtual String getUserName() const override;
    virtual void setUserName(const String) override;

    virtual void setId(const unsigned int) override;
    virtual unsigned int getId() const override;

    virtual String getFileName() const override;
    virtual void setFileName(const String) override;

    virtual void Login() override;
    virtual void Logout() override;
    virtual void Action(const CommandStruct&) override;
    
    virtual bool GetIsHasLog() override;
    virtual unsigned int Hash(const String& str) override;
    virtual int FindUserData(UserStruct&, bool) override;
    virtual void AllUsers(String&) override;
    virtual void SetUpUserData(UserStruct&, Vector<String>&, UserOptions) override;

    virtual void Print() override;
    virtual String BuildUserData() override;
    virtual void Help() override;
    virtual void SaveData() override;

    virtual ~User() {}
};

#endif
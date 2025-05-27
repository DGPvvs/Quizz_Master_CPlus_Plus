#ifndef Admin_H
#define Admin_H

#include "User.h"
/// <summary>
/// Декларация на потребителски клас Администратор
/// </summary>
class Admin : public User
{
public:
    Admin(IWriter*, IReader*, IBaseProvider*);
    virtual void Help() override;
    virtual void Action(const CommandStruct&) override;
    virtual String BuildUserData() override;
    virtual void SaveData() override;

    void Ban(const CommandStruct&);
    void Pending();
    void ApproveQuiz(const CommandStruct&);

    virtual ~Admin() {};
};
#endif
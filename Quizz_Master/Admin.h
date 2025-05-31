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
    virtual void Action(CommandStruct&) override;
    virtual String BuildUserData() override;
    virtual void SaveData() override;

    void Ban(const CommandStruct&);
    void Pending();
    void ApproveQuiz(const CommandStruct&);
    void RejectOrRemoveQuiz(String, String, QuizStatus);
    void ViewReports();

    virtual ~Admin() {};
};
#endif
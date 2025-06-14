#ifndef  Game_H
#define Game_H

#include "IUser.h"
#include "IGame.h"
#include "CommandStruct.h"
#include "IBaseProvider.h"
#include "UserStruct.h"

/// <summary>
/// Клас репрезентиращ методите осъществяващи играта
/// </summary>

class Game : public IGame
{
private:
    IUser* user;
    IReader* reader;
    IWriter* writer;
    IBaseProvider * provider;
    CommandStruct* command;

    unsigned int maxUserId;
    unsigned int maxQuizId;

    void Free();
    void GameLoop();
    void SetCommandStruct();
    void LoadConfig();    

public:
    Game(IWriter*, IReader*, IBaseProvider*);
    ~Game();

    virtual void Init() override;
    virtual void Run() override;
    virtual void Exit() override;

    void LoginUser();
    void LogoutUser();
    void SignupUser();

    void SaveUser();
    void LoadUser(UserStruct& us);

    virtual unsigned int GetMaxQuizId() const override;
    virtual void SetMaxQuizId(unsigned int) override;
    virtual void SaveConfig() override;
};

#endif // ! Game
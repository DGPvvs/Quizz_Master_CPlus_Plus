#ifndef  Game_H
#define Game_H

#include "IUser.h"
#include "IGame.h"
#include "CommandStruct.h"
#include "IBaseProvider.h"
#include "UserStruct.h"

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
    void SaveConfig();

public:
    Game(IWriter*, IReader*, IBaseProvider*);
    ~Game();

    void Init();
    void Run();
    void Exit();

    void LoginUser();
    void LogoutUser();
    void SignupUser();

    void SaveUser();
    void LoadUser(UserStruct& us);

    virtual unsigned int GetMaxQuizId() const override;
    virtual void SetMaxQuizId(unsigned int) override;
};

#endif // ! Game
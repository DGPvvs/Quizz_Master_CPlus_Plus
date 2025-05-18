#ifndef Player_H
#define Player_H

#include "User.h"
#include "IBaseProvider.h"

class Player : public User
{
private:
    enum DatBuild
    {
        VIEW_SELF_PROFILE,
        VIEW_OTHER_PROFILE,
    };

    unsigned int level;
    unsigned int points;
    unsigned int numberCreatedQuizzes;
    unsigned int numberLikedQuizzes;
    unsigned int numberFavoriteQuizzes;
    unsigned int numberFinishedChallenges;
    unsigned int numberSolvedTestQuizzes;
    unsigned int numberSolvedNormalQuizzes;
    unsigned int numberCreatedQuizzesChallengers;

    Vector<String> listCreatedQuizzes;
    Vector<unsigned int> listLikedQuizzes;
    Vector<unsigned int> listFavoriteQuizzes;
    Vector<String> listFinishedChallenges;

    void Init();
    unsigned int PointsForLevel();

public:
    Player(IWriter*, IReader*, IBaseProvider*, UserStruct*, UserOptions);
    Player(IWriter*, IReader*, IBaseProvider*);
    virtual void Help() override;
    virtual void Action(const CommandStruct&) override;
    virtual String BuildUserData() override;
    virtual void SetUpUserData(UserStruct&, Vector<String>&, UserOptions) override;
    virtual void SaveData() override;
    void ViewSelfProfile(DatBuild);
    void ViewOtherProfile(const String&, DatBuild);
    virtual ~Player() {};
};

#endif // !Player_H
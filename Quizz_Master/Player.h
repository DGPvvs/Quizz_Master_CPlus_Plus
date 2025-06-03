#ifndef Player_H
#define Player_H

#include "User.h"
#include "IGame.h"
#include "IBaseProvider.h"
#include "TrueOrFalseQuestion.h"
#include "SingleChoiceQuestion.h"
#include "MultipleChoiceQuestion.h"
#include "ShortAnswerQuestion.h"
#include "MatchingPairsQuestion.h"

class Player : public User
{
private:
    enum DatBuild
    {
        VIEW_SELF_PROFILE,
        VIEW_OTHER_PROFILE,
    };

    enum ChallengerOptions
    {
        NoChallenger,
        CreateChallenger,
        TestQuizChallenger,
        NormalQuizChallenger,
    };

    const String TF = "T/F";
    const String SC = "SC";
    const String MC = "MC";
    const String ShA = "ShA";
    const String MP = "MP";

    unsigned int level;
    unsigned int points;
    unsigned int numberCreatedQuizzes;
    unsigned int numberLikedQuizzes;
    unsigned int numberFavoriteQuizzes;
    unsigned int numberFinishedChallenges;
    unsigned int numberSolvedTestQuizzes;
    unsigned int numberSolvedNormalQuizzes;
    unsigned int numberCreatedQuizzesChallengers;

    IGame* game;

    Vector<String> listCreatedQuizzes;
    Vector<unsigned int> listLikedQuizzes;
    Vector<unsigned int> listFavoriteQuizzes;
    Vector<String> listFinishedChallenges;

    void Init();
    unsigned int PointsForLevel();
    void AddQuizChallenge(ChallengerOptions);
    void AddPoints(unsigned int);
    void AddLevel();

    TrueOrFalseQuestion* CreateTF(String*);
    SingleChoiceQuestion* CreateSC(String*);
    MultipleChoiceQuestion* CreateMC(String*);
    ShortAnswerQuestion* CreateShA(String*);
    MatchingPairsQuestion* CreateMP(String*);

public:
    Player(IWriter*, IReader*, IBaseProvider*, UserStruct*, UserOptions);
    Player(IWriter*, IReader*, IBaseProvider*, IGame*);
    virtual void Help() override;
    virtual void Action(CommandStruct&) override;
    virtual String BuildUserData() override;
    virtual void SetUpUserData(UserStruct&, Vector<String>&, UserOptions) override;
    virtual void SaveData() override;
    void ViewSelfProfile(DatBuild);
    void ViewOtherProfile(const String&, DatBuild);
    void CreateQuiz();
    void Quizzes();
    void ReportQuiz(String, String);
    bool ContainCreatedQuizzes(unsigned int);
    void Message();
    virtual ~Player() {};
};

#endif // !Player_H
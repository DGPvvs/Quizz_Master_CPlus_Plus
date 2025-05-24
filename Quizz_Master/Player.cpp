#include "Player.h"
#include "Quiz.h"
#include "TrueOrFalseQuestion.h"

Player::Player(IWriter* writer, IReader* reader, IBaseProvider* provider, UserStruct* us, UserOptions uo)
    : User::User(writer, reader, provider) 
    , game(nullptr)
{
    this->Init();
    Vector<String> v;
    this->SetUpUserData(*us, v, uo);
    this->SaveData();
}

Player::Player(IWriter* writer, IReader* reader, IBaseProvider* provider, IGame* game)
    : User::User(writer, reader, provider)
    , game(game)
{
    this->Init();    
}

void Player::Init()
{
    Vector<String> a, b;
    Vector<unsigned int> c, d;
    this->listCreatedQuizzes = a;
    this->listLikedQuizzes = c;
    this->listFavoriteQuizzes = d;
    this->listFinishedChallenges = b;
}

void Player::Help()
{
    User::Help();

    this->Writer().WriteLine("view-profile");
    this->Writer().WriteLine("edit-profile");
    this->Writer().WriteLine("view-challeenges");
    this->Writer().WriteLine("view-finished-challeenges");
    this->Writer().WriteLine("view <nickname>");
    this->Writer().WriteLine("messages");
    this->Writer().WriteLine("create-quiz");
    this->Writer().WriteLine("edit-quiz <quiz id>");
    this->Writer().WriteLine("quizzes");
    this->Writer().WriteLine("quizzes <usernane>");
    this->Writer().WriteLine("like-quiz <quiz id>");
    this->Writer().WriteLine("unlike-quiz <quiz id>");
    this->Writer().WriteLine("add-to-favs <quiz id>");
    this->Writer().WriteLine("remove-from-favs <quiz id>");
    this->Writer().WriteLine("start-quiz <quiz id> test | normal (shuffle)");
    this->Writer().WriteLine("save-quiz <quiz id> <filepath>");
    this->Writer().WriteLine("report-quiz <quiz id> <reason>");
}

void Player::Action(const CommandStruct& cmdStr)
{
    User::Action(cmdStr);
        
    if (cmdStr.command == VIEW_PROFILE)
    {
        this->ViewSelfProfile(VIEW_SELF_PROFILE);

    }
    else if (cmdStr.command == VIEW)
    {
        this->ViewOtherProfile(cmdStr.Param1, VIEW_OTHER_PROFILE);
    }
    else if (cmdStr.command == CREATE_QUIZ)
    {
        this->CreateQuiz();
    }
}

void Player::CreateQuiz()
{
    this->Writer().Write("Enter quiz title: ");
    String* quizName = this->Reader().ReadLine();
    
    this->Writer().Write("Enter number of questions: ");
    String* numOfQuestionsString = this->Reader().ReadLine();
    unsigned int numOfQuestions = numOfQuestionsString->StringToInt();

    delete numOfQuestionsString;
    numOfQuestionsString = nullptr;

    unsigned int quizId = this->game->GetMaxQuizId() + 1;
    this->game->SetMaxQuizId(quizId);

    Quiz* quiz = new Quiz(&this->Writer(), &this->Reader(), &this->Provider(), *quizName, this->getUserName(), quizId, numOfQuestions);

    delete quizName;
    quizName = nullptr;

    for (size_t i = 0; i < numOfQuestions; i++)
    {
        this->Writer().Write("Enter question 1 type(T/F, SC, MC, ShA, MP): ");
        String* questionType = this->Reader().ReadLine();

        this->Writer().Write("Enter description: ");
        String* description = this->Reader().ReadLine();

        if (*questionType == TF)
        {
            this->Writer().Write("Enter correct answer(True/False): ");
            String* answer = this->Reader().ReadLine();

            this->Writer().Write("Enter points: ");
            String* pointsString = this->Reader().ReadLine();

            unsigned int points = pointsString->StringToInt();

            TrueOrFalseQuestion* question = new TrueOrFalseQuestion(&this->Writer(), &this->Reader(), *description, *answer, points, false);

            quiz->GetQuestions().push_back(question);

            delete answer;
            answer = nullptr;

            delete pointsString;
            pointsString = nullptr;
        }

        delete questionType;
        questionType = nullptr;

        delete description;
        description = nullptr;
    }


    

    //TODO

    delete quiz;
    quiz = nullptr;
}

unsigned int Player::PointsForLevel()
{
    if (this->level < 10)
    {
        return 1000;
    }
    else if (this->level < 20)
    {
        return 2000;
    }
    else if (this->level < 30)
    {
        return 3000;
    }

    return 4000;
}

void Player::ViewSelfProfile(DatBuild option)
{
    char* arr = new char[2] {'\0'};

    arr[0] = ROW_DATA_SEPARATOR;

    String newLine(arr);    

    String result = this->getName() + " " + this->getUserName() + newLine;
    result += "Level : " + String::UIntToString(this->level);

    if (option == DatBuild::VIEW_SELF_PROFILE)
    {
        arr[0] = '\t';
        result += String(arr) + String::UIntToString(this->PointsForLevel() - this->points) + "/";
        result += String::UIntToString(this->PointsForLevel()) + " Points to next level";
    }

    delete[] arr;
    arr = nullptr;

    result += newLine;

    if (option == DatBuild::VIEW_OTHER_PROFILE)
    {
        result += newLine;
    }

    result += "Created Quizzes:" + newLine;

    for (size_t i = 0; i < this->listCreatedQuizzes.getSize(); i++)
    {
        result += this->listCreatedQuizzes[i] + newLine;
    }

    if (option == DatBuild::VIEW_SELF_PROFILE)
    {
        result += newLine + "Liked Quizzes: ";

        for (size_t i = 0; i < this->listLikedQuizzes.getSize(); i++)
        {
            result += "[" + String::UIntToString(this->listLikedQuizzes[i]) + "]";
        }
        
        result += newLine + "Favorite Quizzes: ";

        for (size_t i = 0; i < this->listFavoriteQuizzes.getSize(); i++)
        {
            result += "[" + String::UIntToString(this->listFavoriteQuizzes[i]) + "]";
        }

        result += newLine;
    } 

    this->Writer().WriteLine(result);
}

void Player::ViewOtherProfile(const String& userName, DatBuild option)
{
    UserStruct* us = new UserStruct();
    UserStruct& refUs = *us;

    us->userName = userName;

    int uo = this->FindUserData(*us, NOT_EXSIST);

    if (uo == UserOptions::NotFound)
    {
        this->Writer().WriteLine("User not found!");
    }
    else if ((uo & UserOptions::AlreadyExisist) == UserOptions::AlreadyExisist)
    {
        Player* otherPlayer = new Player(&Writer(), &Reader(), &Provider(), this->game);

        if (us->id <= 10)
        {
            otherPlayer->Writer().WriteLine("Unable to display profile information!\n The specified user is an administrator");
        }
        else
        {
            Vector<String> v;
            otherPlayer->SetUpUserData(refUs, v, UserOptions::Empty);
            otherPlayer->ViewSelfProfile(DatBuild::VIEW_OTHER_PROFILE);
        }

        delete otherPlayer;
        otherPlayer = nullptr;
    }

    delete us;
    us = nullptr;
}

void Player::SaveData()
{
    String s = this->BuildUserData();
    this->Provider().Action(s, ProviderOptions::UserSave);
}

String Player::BuildUserData()
{
    String result = User::BuildUserData();

    char* arr = new char[2] {'\0'};

    arr[0] = ROW_DATA_SEPARATOR;

    String newLine(arr);

    delete[] arr;
    arr = nullptr;

    result += String::UIntToString(this->level) + newLine;
    result += String::UIntToString(this->points) + newLine;
    result += String::UIntToString(this->numberCreatedQuizzes) + newLine;
    result += String::UIntToString(this->numberLikedQuizzes) + newLine;
    result += String::UIntToString(this->numberFavoriteQuizzes) + newLine;
    result += String::UIntToString(this->numberFinishedChallenges) + newLine;
    result += String::UIntToString(this->numberSolvedTestQuizzes) + newLine;
    result += String::UIntToString(this->numberSolvedNormalQuizzes) + newLine;
    result += String::UIntToString(this->numberCreatedQuizzesChallengers) + newLine;

    for (size_t i = 0; i < this->listCreatedQuizzes.getSize(); i++)
    {        
        result = result + this->listCreatedQuizzes[i] + newLine;
    }

    for (size_t i = 0; i < this->listLikedQuizzes.getSize(); i++)
    {
        result = result + String::UIntToString(this->listLikedQuizzes[i]) + newLine;
    }

    for (size_t i = 0; i < this->listFavoriteQuizzes.getSize(); i++)
    {
        result = result + String::UIntToString(this->listFavoriteQuizzes[i]) + newLine;
    }

    for (size_t i = 0; i < this->listFinishedChallenges.getSize(); i++)
    {
        result = result + this->listFinishedChallenges[i] + newLine;
    }    

    return result;
}

void Player::SetUpUserData(UserStruct& us, Vector<String>& v, UserOptions uo)
{
    User::SetUpUserData(us, v, uo);

    if ((uo & UserOptions::NewUserCreated) == UserOptions::NewUserCreated)
    {
        this->level = 0;
        this->points = 0;
        this->numberCreatedQuizzes = 0;
        this->numberLikedQuizzes = 0;
        this->numberFavoriteQuizzes = 0;
        this->numberFinishedChallenges = 0;
        this->numberSolvedTestQuizzes = 0;
        this->numberSolvedNormalQuizzes = 0;
        this->numberCreatedQuizzesChallengers = 0;
        return;
    }

    this->level = v[2].StringToInt();
    this->points = v[3].StringToInt();
    this->numberCreatedQuizzes = v[4].StringToInt();
    this->numberLikedQuizzes = v[5].StringToInt();
    this->numberFavoriteQuizzes = v[6].StringToInt();
    this->numberFinishedChallenges = v[7].StringToInt();
    this->numberSolvedTestQuizzes = v[8].StringToInt();
    this->numberSolvedNormalQuizzes = v[9].StringToInt();
    this->numberCreatedQuizzesChallengers = v[10].StringToInt();

    int i = 11;
    int j = i;

    for (; i < j + this->numberCreatedQuizzes; ++i)
    {
        this->listCreatedQuizzes.push_back(v[i]);
    }

    j = i;

    for (; i < j + this->numberLikedQuizzes; ++i)
    {
        this->listLikedQuizzes.push_back(v[i].StringToInt());
    }

    j = i;

    for (; i < j + this->numberFavoriteQuizzes; ++i)
    {
        this->listFavoriteQuizzes.push_back(v[i].StringToInt());
    }

    j = i;

    for (; i < j + this->numberFinishedChallenges; ++i)
    {
        this->listFinishedChallenges.push_back(v[i]);
    }

    /*0 <firstName>
    1 <lastName>
    2 <level>
    3 <points>
    4 <numberCreatedQuizzes>
    5 <numberLikedQuizzes>
    6 <numberFavoriteQuizzes>
    7 <numberFinishedChallenges>
    8 <numberSolvedTestQuizzes>
    9 <numberSolvedNormalQuizzes>
   10 <numberCreatedQuizzesChallengers>
   <numberCreatedQuizzes lines of created quizes in format>:
   <quizId>#<quizName>
   .
   .
   .
   <numberLikedQuizzes lines of liked quizzes in format>:
   <quizId>
   .
   .
   .
   <numberFavoriteQuizzes lines of favorite quizzes in format>:
   <quizId>
   .
   .
   .
   <numberFinishedChallenges lines of finished challenges in format>
   <<data>|<text challenges>>
   .
   .
   .*/

}


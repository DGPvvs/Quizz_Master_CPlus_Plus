#include "Player.h"

Player::Player(IWriter* writer, IReader* reader, IBaseProvider* provider, UserStruct& us, UserOptions uo)
    : User::User(writer, reader, provider) 
{
    this->Init();
    Vector<String> v;
    this->SetUpUserData(us, v, uo);
    this->SaveData();
}

Player::Player(IWriter* writer, IReader* reader, IBaseProvider* provider)
    : User::User(writer, reader, provider)
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
    //TODO
}

void Player::Action(const CommandStruct& cndStr)
{
    User::Action(cndStr);
}

void Player::SaveData()
{
    String s = this->BuildUserData();
    this->Provider().Action(s, ProviderOptions::UserSave);

    //TODO Да направя метод за запис на данните на плеара във собствен файл с име указано от 
}

String Player::BuildUserData()
{
    String result = User::BuildUserData();

    char* arr = new char[2] {'\0'};

    arr[0] = ROW_DATA_SEPARATOR;

    String newLine(arr);

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
        //TODO зарежда данните за новосъздаден Player
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


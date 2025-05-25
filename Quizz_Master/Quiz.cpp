#include "Quiz.h"
#include "UserStruct.h"
#include "User.h"

Quiz::Quiz(IWriter* writer, IReader* reader, IBaseProvider* provider, String name, String userName, unsigned int id, unsigned int numberOfQuestions)
    : writer(writer)
    , reader(reader)
    , provider(provider)
    , quizName(name)
    , userName(userName)
    , id(id)
    , numberOfQuestions(numberOfQuestions)
{
}

Quiz::~Quiz()
{
    for (size_t i = 0; i < this->questions.getSize(); i++)
    {
        delete& this->questions[i];
    }
}

String Quiz::GetQuizName()const
{
    return this->quizName;
}

String Quiz::GetUserName()const
{
    return this->userName;
}

String Quiz::GetUserFullName()const
{
    UserStruct* us = new UserStruct();
    UserStruct& refUs = *us;

    us->userName = userName;

    User* user = new User(writer, reader, provider);

    int uo = user->FindUserData(*us, NOT_EXSIST);

    String result = us->firstName + " " + us->lastName;

    delete user;
    user = nullptr;

    return result;
}

unsigned int Quiz::GetNumberOfQuestions()const
{
    return this->numberOfQuestions;
}

unsigned int Quiz::GetId()const
{
    return this->id;
}

Vector<IQuestion*> Quiz::GetQuestions()const
{
    return this->questions;
}

void Quiz::SaveQuiz(QuizStatus qs)
{
    if (qs == QuizStatus::NewQuiz)
    {
        String s = QUIZZES_FILE_NAME;

        this->provider->Action(s, ProviderOptions::QuizzeFind);

        Vector<String> v;

        String::Split(ROW_DATA_SEPARATOR, v, s);

        String quizFileName = String::UIntToString(this->GetId()) + "Quiz.txt";

        String newQuizString = String::UIntToString(this->GetId()) + " " + quizFileName + " " + String::UIntToString(QuizStatus::NewQuiz);

        v.push_back(newQuizString);

        String allQuizzesString;
        String::Join(ROW_DATA_SEPARATOR, v, allQuizzesString);

        char* arr = new char[2] {'\0'};

        arr[0] = FILENAME_TO_DATA_SEPARATOR;

        allQuizzesString = QUIZZES_FILE_NAME + String(arr) + allQuizzesString;

        this->provider->Action(allQuizzesString, ProviderOptions::QuizzeIndexSave);
    }
    //TODO
}
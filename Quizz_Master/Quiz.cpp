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

        if (s == ERROR)
        {
            s = EMPTY_STRING;
        }

        Vector<String> v;

        String::Split(ROW_DATA_SEPARATOR, v, s);

        char* arr = new char[2] {'\0'};

        arr[0] = QUIZ_ELEMENT_DATA_SEPARATOR;

        String separator = String(arr);

        String quizFileName = String::UIntToString(this->GetId()) + "Quiz.txt";

        String newQuizString = String::UIntToString(this->GetId()) + separator + this->GetQuizName() + separator + this->GetUserName() + separator + quizFileName + separator + String::UIntToString(QuizStatus::NewQuiz);

        v.push_back(newQuizString);

        String allQuizzesString;
        String::Join(ROW_DATA_SEPARATOR, v, allQuizzesString);        

        arr[0] = FILENAME_TO_DATA_SEPARATOR;

        allQuizzesString = QUIZZES_FILE_NAME + String(arr) + allQuizzesString;        

        this->provider->Action(allQuizzesString, ProviderOptions::QuizzeIndexSave);

        delete[] arr;
        arr = nullptr;
    }

    char* arr = new char[2] {'\0'};

    String s = PENDING_FILE_NAME;

    this->provider->Action(s, ProviderOptions::QuizzeFind);

    if (s == ERROR)
    {
        s = EMPTY_STRING;
    }

    Vector<String> pendingVec;

    String::Split(ROW_DATA_SEPARATOR, pendingVec, s);

    char* arr1 = new char[2] {'\0'};

    arr1[0] = QUIZ_ELEMENT_DATA_SEPARATOR;

    String separator = String(arr1);

    String newPendingString = String::UIntToString(this->GetId()) + separator + this->GetQuizName() + separator + this->GetUserName();

    pendingVec.push_back(newPendingString);

    String allPendingString;
    String::Join(ROW_DATA_SEPARATOR, pendingVec, allPendingString);

    arr1[0] = FILENAME_TO_DATA_SEPARATOR;

    allPendingString = PENDING_FILE_NAME + String(arr1) + allPendingString;

    this->provider->Action(allPendingString, ProviderOptions::QuizzeIndexSave);

    arr1[0] = QUOTES_DATA_SEPARATOR;


    this->writer->WriteLine("Quiz " + String(arr1) + this->GetQuizName() + String(arr1) + " with ID " + String::UIntToString(this->GetId()) + " sent for admin approval!");
    //TODO

    delete[] arr1;
    arr1 = nullptr;
}
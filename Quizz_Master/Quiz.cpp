#include "Quiz.h"
#include "UserStruct.h"
#include "User.h"

Quiz::Quiz(IWriter* writer, IReader* reader, IBaseProvider* provider, String name, String userName, unsigned int id, unsigned int numberOfQuestions)
    : writer(writer)
    , reader(reader)
    , provider(provider)
    , quizName(name)
    , id(id)
    , numberOfQuestions(numberOfQuestions)
{
    //this->questions = new Vector<IQuestion*>(this->numberOfQuestions);
    //this->questions = new Vector<IQuestion*>();
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
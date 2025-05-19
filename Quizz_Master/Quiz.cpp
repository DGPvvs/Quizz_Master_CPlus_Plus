#include "Quiz.h"

Quiz::Quiz(IWriter* writer, IReader* reader, IBaseProvider* provider, String name, String userName, unsigned int id, unsigned int numberOfQuestions)
    : writer(writer)
    , reader(reader)
    , provider(provider)
    , quizName(name)
    , id(id)
    , numberOfQuestions(numberOfQuestions)
{
    this->questions = new Vector<IQuestion*>(this->numberOfQuestions);
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
    //TODO
    return String(EMPTY_STRING);
}

unsigned int Quiz::GetNumberOfQuestions()const
{
    return this->numberOfQuestions;
}

unsigned int Quiz::GetId()const
{
    return this->id;
}



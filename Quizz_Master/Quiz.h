#ifndef Quiz_H
#define Quiz_H

#include "String.h"
#include "IWriter.h"
#include "IReader.h"
#include "IBaseProvider.h"
#include "IQuestion.h"

class Quiz
{
private:
    String quizName;
    unsigned int id;
    unsigned int numberOfQuestions;
    String userName;

    IWriter* writer;
    IReader* reader;
    IBaseProvider* provider;

    Vector<IQuestion*>* questions;

public:
    Quiz(IWriter* writer, IReader* reader, IBaseProvider* provider, String name, String userName, unsigned int id, unsigned int numberOfQuestions);
    String GetQuizName()const;
    String GetUserName()const;
    String GetUserFullName()const;
    unsigned int GetNumberOfQuestions()const;
    unsigned int GetId()const;
};

#endif


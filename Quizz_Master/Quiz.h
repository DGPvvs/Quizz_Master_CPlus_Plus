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
    unsigned int id;
    unsigned int numberOfQuestions;
    unsigned int numberOfLikes;
    String quizName;
    String userName;

    IWriter* writer;
    IReader* reader;
    IBaseProvider* provider;

    Vector<IQuestion*> questions;

public:
    Quiz(IWriter*, IReader*, IBaseProvider*, String, String, unsigned int, unsigned int, unsigned int);
    ~Quiz() = default;
    String GetQuizName() const;
    String GetUserName() const;
    String GetUserFullName() const;
    unsigned int GetNumberOfQuestions() const;
    unsigned int GetId() const;
    unsigned int GetLikes() const;
    void IncrementLikes(int);
    Vector<IQuestion*>& GetQuestions();
    void SaveQuiz(QuizStatus, unsigned int);
    String FindAllQuizzes();
};

#endif


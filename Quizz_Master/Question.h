#ifndef Question_H
#define Question_H

#include "String.h"
#include "IWriter.h"
#include "IReader.h"

class Question
{
private:
    bool isTest;
    unsigned int points;
    String correctAnswer;
    String description;


    IWriter* writer;
    IReader* reader;

protected:
    String GetDescription() const;
    unsigned int GetPoints() const;
    String GetCorrectAnswer() const;
    bool GetIsTest() const;
    void PrintQuestion();
    void PrintTestCondition();

    IReader* Reader();
    IWriter* Writer();

    virtual bool AnswerAQuestion();

public:
    Question(IWriter*, IReader*, String&, String&, unsigned int, bool);
    virtual ~Question() {};
};

#endif // !Question_H

#ifndef Question_H
#define Question_H

#include "String.h"
#include "IWriter.h"
#include "IReader.h"
#include "GlobalConstants.h"

class Question
{
private:
    bool isTest;
    unsigned char numOfAnswers;
    unsigned int points;
    QuestionType qt;
    String correctAnswer;
    String description;

    IWriter* writer;
    IReader* reader;

protected:
    String GetDescription() const;
    unsigned int GetPoints() const;
    void SetPoints(unsigned int);
    int GetQt() const;
    void SetQt(QuestionType);
    String GetCorrectAnswer() const;
    bool GetIsTest() const;
    unsigned char GetNumOfAnswers() const;

    void PrintTestCondition();

    IReader* Reader();
    IWriter* Writer();

    virtual void PrintQuestion();
    virtual bool AnswerAQuestion();

public:
    Question(IWriter*, IReader*, String&, String&, unsigned int, bool, unsigned char);
    virtual ~Question() {};
};

#endif // !Question_H

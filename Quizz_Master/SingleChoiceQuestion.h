#ifndef SingleChoiceQuestion_H
#define SingleChoiceQuestion_H

#include "Question.h"
#include "IQuestion.h"

class SingleChoiceQuestion : public Question, public IQuestion
{
private:
    Vector<String> questions;

protected:

public:
    Vector<String>& GetQuestions();

    virtual unsigned int Action() override;
    virtual void SetUpData(String&) override;
    virtual String BuildQuestionData() override;
    virtual void PrintQuestion() override;
    virtual bool AnswerAQuestion() override;
    virtual String ToStringFile() override;

    SingleChoiceQuestion(IWriter*, IReader*, String&, String&, unsigned int, bool);
    SingleChoiceQuestion(IWriter*, IReader*, String&, String&, unsigned int, bool, unsigned int);

    virtual ~SingleChoiceQuestion() {};
};

#endif // !SingleChoiceQuestion_H



#ifndef MultipleChoiceQuestion_H
#define MultipleChoiceQuestion_H

#include "SingleChoiceQuestion.h"
#include "IQuestion.h"

class MultipleChoiceQuestion : public SingleChoiceQuestion
{
private:
	Vector<String> questions;
    unsigned char percent;

public:
    virtual bool AnswerAQuestion() override;

    MultipleChoiceQuestion(IWriter*, IReader*, String&, String&, unsigned int, bool, unsigned int);

    virtual ~MultipleChoiceQuestion() {};
};

#endif // !MultipleChoiceQuestion_H




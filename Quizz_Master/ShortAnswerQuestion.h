#ifndef ShortAnswerQuestion_H
#define ShortAnswerQuestion_H

#include "TrueOrFalseQuestion.h"

class ShortAnswerQuestion : public TrueOrFalseQuestion
{
public:
	ShortAnswerQuestion(IWriter*, IReader*, String&, String&, unsigned int, bool);
	virtual ~ShortAnswerQuestion() {};
};

#endif // !ShortAnswerQuestion_H
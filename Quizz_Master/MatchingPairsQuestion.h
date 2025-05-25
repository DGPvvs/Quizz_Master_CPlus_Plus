#ifndef MatchingPairsQuestion_H
#define MatchingPairsQuestion_H

#include "MultipleChoiceQuestion.h"

class MatchingPairsQuestion : public MultipleChoiceQuestion
{
private:
	Vector<String> answers;

public:
	MatchingPairsQuestion(IWriter*, IReader*, String&, String&, unsigned int, bool, unsigned int);

	Vector<String>& GetAnswersVec();

	virtual ~MatchingPairsQuestion() {};
};

#endif // !MatchingPairsQuestion_H


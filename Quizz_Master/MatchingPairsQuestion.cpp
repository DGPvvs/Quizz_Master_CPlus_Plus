#include "MatchingPairsQuestion.h"

MatchingPairsQuestion::MatchingPairsQuestion(IWriter* writer, IReader* reader, String& description, String& correctAnswer, unsigned int points, bool isTest, unsigned int questionsCount)
    : MultipleChoiceQuestion::MultipleChoiceQuestion(writer, reader, description, correctAnswer, points, isTest, questionsCount)
{
    this->SetQt(QuestionType::MP);
}

Vector<String>& MatchingPairsQuestion::GetAnswersVec()
{
    return this->answers;
}

void MatchingPairsQuestion::SetUpData(String& s)
{
    throw "NotImplement - void MatchingPairsQuestion::SetUpData(String& s)";
    //TODO
}


String MatchingPairsQuestion::BuildQuestionData()
{
    String result = MultipleChoiceQuestion::BuildQuestionData();

    result += MP_SEPARATOR_STRING + NEW_LINE;

    for (size_t i = 0; i < this->answers.getSize(); i++)
    {
        result += this->answers[i] + NEW_LINE;
    }

    return result;
}
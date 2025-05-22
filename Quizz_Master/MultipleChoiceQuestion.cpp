#include "MultipleChoiceQuestion.h"
#include "GlobalConstants.h"


MultipleChoiceQuestion::MultipleChoiceQuestion(IWriter* writer, IReader* reader, String& description, String& correctAnswer, unsigned int points, bool isTest, unsigned int questionsCount = 4)
    : SingleChoiceQuestion::SingleChoiceQuestion(writer, reader, description, correctAnswer, points, isTest, questionsCount)
{

}

bool MultipleChoiceQuestion::AnswerAQuestion()
{    
    bool result = false;

    String* answer = this->Reader()->ReadLine();

    //TODO

    if (*answer == this->GetCorrectAnswer())
    {
        result = true;
    }

    delete answer;
    answer = nullptr;

    return result;
}

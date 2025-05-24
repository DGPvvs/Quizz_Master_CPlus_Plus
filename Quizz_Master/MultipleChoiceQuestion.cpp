#include "MultipleChoiceQuestion.h"
#include "GlobalConstants.h"


MultipleChoiceQuestion::MultipleChoiceQuestion(IWriter* writer, IReader* reader, String& description, String& correctAnswer, unsigned int points, bool isTest, unsigned int questionsCount = 4)
    : SingleChoiceQuestion::SingleChoiceQuestion(writer, reader, description, correctAnswer, points, isTest, questionsCount)
    , percent(0)
{
    this->SetQt(QuestionType::MC);
}

void MultipleChoiceQuestion::SeparateAnswers(Vector<String>& v, String s)
{
    String::Split(ELEMENT_DATA_SEPARATOR, v, s);

    Vector<String> tmp;

    for (size_t i = 0; i < v.getSize(); i++)
    {
        tmp.clear();
        String::Split(COMMA_DATA_SEPARATOR, tmp, v[i]);

        for (size_t j = 0; j < tmp.getSize(); j++)
        {
            v.push_back(tmp[j]);
        }
    }
}

bool MultipleChoiceQuestion::AnswerAQuestion()
{    
    bool result = false;

    String* answer = this->Reader()->ReadLine();

    Vector<String> correctAnswersVec, answersVec;

    this->SeparateAnswers(correctAnswersVec, this->GetCorrectAnswer());
    this->SeparateAnswers(answersVec, *answer);

    unsigned int countCorrectAnswers = 0;

    for (size_t i = 0; i < answersVec.getSize(); i++)
    {
        for (size_t j = 0; j < correctAnswersVec.getSize(); j++)
        {
            if (answersVec[i] == correctAnswersVec[j])
            {
                countCorrectAnswers++;
                break;
            }
        }
    }

    this->percent = 100.0 * countCorrectAnswers / this->GetNumOfAnswers();

    if (this->percent > 0)
    {
        result = true;
        this->SetPoints(percent * this->GetPoints() / 100);
    }

    delete answer;
    answer = nullptr;

    return result;
}

#include "TrueOrFalseQuestion.h"
#include "GlobalConstants.h"

TrueOrFalseQuestion::TrueOrFalseQuestion(IWriter* writer, IReader* reader, String& description, String& corectAnswer, unsigned int points, bool isTest)
    : Question::Question(writer, reader, description, corectAnswer, points, isTest)
{

}

unsigned int TrueOrFalseQuestion::Action()
{
    unsigned int result = this->GetPoints();

    this->PrintQuestion();

    if (!this->AnswerAQuestion())
    {
        result = 0;
    }
    this->Writer()->WriteLine(EMPTY_STRING);

    this->PrintTestCondition();

    return result;
}

void TrueOrFalseQuestion::SetUpData(String& dataString)
{
    //TODO
}

String TrueOrFalseQuestion::BuildQuestionData()
{
    char* arr = new char[2] {'\0'};
    arr[0] = ROW_DATA_SEPARATOR;
    String newLine(arr);

    delete[] arr;

    String result = String::UIntToString(QuestionType::TF) + newLine;
    result += this->GetDescription() + newLine;
    result += this->GetCorrectAnswer() + newLine;
    result += String::UIntToString(this->GetPoints()) + newLine;

    return result;
}

bool TrueOrFalseQuestion::AnswerAQuestion()
{
    bool result = false;

    String* answer = this->Reader()->ReadLine();

    if (*answer == this->GetCorrectAnswer())
    {
        result = true;
    }

    delete answer;
    answer = nullptr;

    return result;
}
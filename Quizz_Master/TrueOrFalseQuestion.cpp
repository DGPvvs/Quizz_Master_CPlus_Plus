#include "TrueOrFalseQuestion.h"
#include "GlobalConstants.h"

TrueOrFalseQuestion::TrueOrFalseQuestion(IWriter* writer, IReader* reader, String& description, String& correctAnswer, unsigned int points, bool isTest)
    : Question::Question(writer, reader, description, correctAnswer, points, isTest, 1)
{
    this->SetQt(QuestionType::TF);
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

String TrueOrFalseQuestion::ToStringFile()
{
    String result = this->GetDescription() + NEW_LINE;
    result += this->GetCorrectAnswer() + NEW_LINE;

    return result;
}

String TrueOrFalseQuestion::BuildQuestionData()
{
    char* arr = new char[2] {'\0'};
    arr[0] = ROW_DATA_SEPARATOR;
    String newLine(arr);

    delete[] arr;

    String result = String::UIntToString(this->GetQt()) + newLine;
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

void TrueOrFalseQuestion::PrintQuestion()
{
    this->Writer()->WriteLine(this->GetDescription() + "\t(" + String::UIntToString(this->GetPoints()) + " points)");
    Question::PrintQuestion();
}
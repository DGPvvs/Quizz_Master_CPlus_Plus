#include "SingleChoiceQuestion.h"
#include "GlobalConstants.h"

SingleChoiceQuestion::SingleChoiceQuestion(IWriter* writer, IReader* reader, String& description, String& correctAnswer, unsigned int points, bool isTest)
    : Question::Question(writer, reader, description, correctAnswer, points, isTest, 4)
{
    this->SetQt(QuestionType::SC);
}

SingleChoiceQuestion::SingleChoiceQuestion(IWriter* writer, IReader* reader, String& description, String& correctAnswer, unsigned int points, bool isTest, unsigned int questionsCount)
    : Question::Question(writer, reader, description, correctAnswer, points, isTest, questionsCount)
{
    this->SetQt(QuestionType::SC);
}

Vector<String>& SingleChoiceQuestion::GetQuestions()
{
    return this->questions;
}

unsigned int SingleChoiceQuestion::Action()
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

void SingleChoiceQuestion::SetUpData(String& dataString)
{
    Vector<String> quest;

    String::Split(ROW_DATA_SEPARATOR, quest, dataString);

    for (int i = 0; i < quest.getSize(); ++i)
    {
        this->questions.push_back(quest[i]);
    }
}

String SingleChoiceQuestion::BuildQuestionData()
{
    char* arr = new char[2] {'\0'};
    arr[0] = ROW_DATA_SEPARATOR;
    String newLine(arr);

    delete[] arr;

    String result = String::UIntToString(this->GetQt()) + newLine;
    result += this->GetDescription() + newLine;
    result += this->GetCorrectAnswer() + newLine;
    result += String::UIntToString(this->GetPoints()) + newLine;

    for (int i = 0; i < this->questions.getSize(); ++i)
    {
        result += this->questions[i] + newLine;
    }

    return result;
}

void SingleChoiceQuestion::PrintQuestion()
{
    this->Writer()->WriteLine(this->GetDescription() + "\t(" + String::UIntToString(this->GetPoints()) + " points)");

    for (int i = 0; i < this->questions.getSize(); ++i)
    {
        this->Writer()->WriteLine("this.questions[i]");
    }

    Question::PrintQuestion();
}

bool SingleChoiceQuestion::AnswerAQuestion()
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
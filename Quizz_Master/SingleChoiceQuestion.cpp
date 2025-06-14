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
    String result = String::UIntToString(this->GetQt()) + NEW_LINE;
    result += this->GetDescription() + NEW_LINE;
    result += this->GetCorrectAnswer() + NEW_LINE;
    result += String::UIntToString(this->GetPoints()) + NEW_LINE;
    result += String::UIntToString(this->questions.getSize()) + NEW_LINE;

    for (int i = 0; i < this->questions.getSize(); ++i)
    {
        result += this->questions[i] + NEW_LINE;
    }

    return result;

    //Тип на въпроса
    //въпроса
    //Верни отговори
    //точки
    //брой отговори
    //... изброяване на възможните отговори

}

void SingleChoiceQuestion::PrintQuestion()
{
    this->Writer()->WriteLine(this->GetDescription() + "\t(" + String::UIntToString(this->GetPoints()) + " points)");

    char* arr = new char[2] {'\0'};

    for (int i = 0; i < this->questions.getSize(); ++i)
    {        
        arr[0] = 'A' + i;
        
        this->Writer()->WriteLine(String(arr) + ") " + this->questions[i]);
    }

    delete[] arr;
    arr = nullptr;

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

String SingleChoiceQuestion::ToStringFile()
{
    String result = "Description: " + this->GetDescription() + NEW_LINE;

    char* arr = new char[2] {'\0'};

    result += "Posible answers:" + NEW_LINE;

    for (size_t i = 0; i < this->GetQuestions().getSize(); i++)
    {
        arr[0] = 'a' + i;
        String questNum = String(arr);

        result += questNum + ") " + this->GetQuestions()[i] + NEW_LINE;
    }

    delete[] arr;
    arr = nullptr;

    result += "Correct answer: " + this->GetCorrectAnswer() + NEW_LINE;

    return result;
}
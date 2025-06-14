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

    result += String::UIntToString(this->answers.getSize()) + NEW_LINE;

    for (size_t i = 0; i < this->answers.getSize(); i++)
    {
        result += this->answers[i] + NEW_LINE;
    }

    return result;

    //Тип на въпроса
    //въпроса
    //Верни отговори
    //точки
    //брой отговори
    //... изброяване на възможните отговори
    //брой малки отговори
    //... изброяване на възможните малки отговори
}

String MatchingPairsQuestion::ToStringFile()
{
    String result = "Description: " + this->GetDescription() + NEW_LINE;

    char* arr = new char[2] {'\0'};

    result += "First group answers:" + NEW_LINE;

    for (size_t i = 0; i < this->GetQuestions().getSize(); i++)
    {
        arr[0] = 'A' + i;
        String questNum = String(arr);

        result += questNum + ") " + this->GetQuestions()[i] + NEW_LINE;
    }

    result += "Second group answers:" + NEW_LINE;

    for (size_t i = 0; i < this->GetAnswersVec().getSize(); i++)
    {
        arr[0] = 'a' + i;
        String questNum = String(arr);

        result += questNum + ") " + this->GetAnswersVec()[i] + NEW_LINE;
    }

    delete[] arr;
    arr = nullptr;

    result += "Correct answer: " + this->GetCorrectAnswer() + NEW_LINE;

    return result;
}

void MatchingPairsQuestion::PrintQuestion()
{
    this->Writer()->WriteLine(this->GetDescription() + "\t(" + String::UIntToString(this->GetPoints()) + " points)");
    char* arr = new char[2] {'\0'};

    for (int i = 0; i < this->GetQuestions().getSize(); ++i)
    {
        arr[0] = 'A' + i;
        this->Writer()->WriteLine(String(arr) + ") " + this->GetQuestions()[i]);
    }

    this->Writer()->WriteLine(EMPTY_STRING);

    for (int i = 0; i < this->GetAnswersVec().getSize(); ++i)
    {
        arr[0] = 'a' + i;
        this->Writer()->WriteLine(String(arr) + ") " + this->GetAnswersVec()[i]);
    }

    delete[] arr;
    arr = nullptr;

    Question::PrintQuestion();
}
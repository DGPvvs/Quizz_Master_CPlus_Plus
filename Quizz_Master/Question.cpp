#include "Question.h"

String Question::GetDescription() const
{
    return this->description;
}

unsigned int Question::GetPoints() const
{
    return this->points;
}

String Question::GetCorrectAnswer() const
{
    return this->correctAnswer;
}

bool Question::GetIsTest() const
{
    return this->isTest;
}

void Question::PrintQuestion()
{
    this->Writer()->Write("Enter your answer here: ");
}

void Question::PrintTestCondition()
{
    if (this->GetIsTest())
    {
        this->writer->WriteLine("The correct answer is: " + this->correctAnswer);
    }
}

Question::Question(IWriter* writer, IReader* reader, String& description, String& correctAnswer, unsigned int points, bool isTest, unsigned char numOfAnswers)
    : writer(writer)
    , reader(reader)
    , description(description)
    , correctAnswer(correctAnswer)
    , points(points)
    , isTest(isTest)
    , numOfAnswers(numOfAnswers)
{

}

IReader* Question::Reader()
{
    return this->reader;
}

IWriter* Question::Writer()
{
    return this->writer;
}

bool Question::AnswerAQuestion()
{
    return true;
}

unsigned char Question::GetNumOfAnswers() const
{
    return this->numOfAnswers;
}
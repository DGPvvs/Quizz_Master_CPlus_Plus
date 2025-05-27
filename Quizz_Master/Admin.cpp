#include "Admin.h"

/// <summary>
/// Конструктор
/// </summary>
/// <param name="writer"></param>
/// <param name="reader"></param>
/// <param name="provider"></param>
Admin::Admin(IWriter* writer, IReader* reader, IBaseProvider* provider)
	: User::User(writer, reader, provider)
{
}

/// <summary>
/// Метод извеждащ функционалностите на Admin
/// </summary>
void Admin::Help()
{
	User::Help();

	this->Writer().WriteLine("pending");
	this->Writer().WriteLine("approve-quiz <quiz id>");
	this->Writer().WriteLine("reject-quiz <quiz id> <reason>");
	this->Writer().WriteLine("view-reports");
	this->Writer().WriteLine("remove-quiz <quiz id> <reason>");
	this->Writer().WriteLine("ban <username>");
}

void Admin::ApproveQuiz(const CommandStruct& cmdStr)
{
	String quizId = cmdStr.Param1;
	String s = this->GetQuiz().FindAllQuizzes();

	Vector<String> quizzesVec, quizVec;

	String::Split(ROW_DATA_SEPARATOR, quizzesVec, s);

	for (size_t i = 0; i < quizzesVec.getSize(); i++)
	{
		quizVec.clear();
		String quizString = quizzesVec[i];

		String::Split(QUIZ_ELEMENT_DATA_SEPARATOR, quizVec, quizString);
		String id = quizVec[0];

		if (id == quizId)
		{
			Vector<String> v;
			quizVec[4] = String::UIntToString(QuizStatus::ApprovedQuiz);

			for (size_t j = 0; j < quizVec.getSize(); j++)
			{
				v.push_back(quizVec[j]);
			}

			s = EMPTY_STRING;
			String::Join(QUIZ_ELEMENT_DATA_SEPARATOR, v, s);
			quizzesVec[i] = s;
			break;
		}
	}

	char* arr = new char[2] {'\0'};

	String allQuizzesString;
	String::Join(ROW_DATA_SEPARATOR, quizzesVec, allQuizzesString);

	arr[0] = FILENAME_TO_DATA_SEPARATOR;

	allQuizzesString = QUIZZES_FILE_NAME + String(arr) + allQuizzesString;

	this->Provider().Action(allQuizzesString, ProviderOptions::QuizzeIndexSave);

	delete[] arr;
	arr = nullptr;

	//id|quizName|useName|quizFileName|QuizStatus|numOfQuestions|Likes
}

void Admin::Ban(const CommandStruct& cmdStr)
{
	UserStruct* us = new UserStruct();

	us->firstName = EMPTY_STRING;
	us->lastName = EMPTY_STRING;
	us->userName = cmdStr.Param1;
	us->password = EMPTY_STRING;

	Vector<String> usersVec, v;
	String users;
	this->AllUsers(users);
	String::Split(ROW_DATA_SEPARATOR, usersVec, users);

	int userIndex = this->FindUserIndex(*us, usersVec);	

	if (userIndex < 0)
	{
		this->Writer().WriteLine("No user with that name found!");

		delete us;
		us = nullptr;

		return;
	}	

	String::Split(ELEMENT_DATA_SEPARATOR, v, usersVec[userIndex]);

	if (v[3].StringToInt() <= 10)
	{
		this->Writer().WriteLine("Banning an administrator is not allowed!");
	}
	else
	{
		v[4] = String::UIntToString(UserOptions::Empty | UserOptions::Ban);
		String s, s1;

		String::Join(ELEMENT_DATA_SEPARATOR, v, s);

		usersVec[userIndex] = s;
		String::Join(ROW_DATA_SEPARATOR, usersVec, s1);

		this->Provider().Action(s1, ProviderOptions::NewUserSave);
	}

	delete us;
	us = nullptr;
}

void Admin::Pending()
{
	String s = this->GetQuiz().FindAllQuizzes();

	Vector<String> quizzesVec, quizVec;

	String::Split(ROW_DATA_SEPARATOR, quizzesVec, s);

	for (size_t i = 0; i < quizzesVec.getSize(); i++)
	{
		quizVec.clear();
		String quizString = quizzesVec[i];

		String::Split(QUIZ_ELEMENT_DATA_SEPARATOR, quizVec, quizString);

		if (quizVec[4].StringToInt() == QuizStatus::NewQuiz || quizVec[4].StringToInt() == QuizStatus::EditQuiz)
		{
			String output = "[id " + quizVec[0] + "] " + quizVec[1] + " by " + quizVec[2];
			this->Writer().WriteLine(output);
		}
	}
}

void Admin::Action(const CommandStruct& cmdStr)
{
	User::Action(cmdStr);

	if (cmdStr.command == BAN)
	{
		this->Ban(cmdStr);
	}
	else if (cmdStr.command == PENDING)
	{
		this->Pending();
	}
	else if (cmdStr.command == APPROVE_QUIZ)
	{
		this->ApproveQuiz(cmdStr);
	}
}

String Admin::BuildUserData()
{
	String result = User::BuildUserData();
	return result;
}

void Admin::SaveData()
{

}
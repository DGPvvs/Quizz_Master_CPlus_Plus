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
	this->Writer().WriteLine("approve-quiz <quiz id>");
	this->Writer().WriteLine("reject-quiz <quiz id> <reason>");
	this->Writer().WriteLine("view-reports");
	this->Writer().WriteLine("ban <username>");
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

void Admin::Action(const CommandStruct& cmdStr)
{
	User::Action(cmdStr);

	if (cmdStr.command == BAN)
	{
		this->Ban(cmdStr);
	}
	else if (cmdStr.command == PENDING)
	{
		String s = QUIZZES_FILE_NAME;

		this->Provider().Action(s, ProviderOptions::QuizzeFind);

		if (s == ERROR)
		{
			s = EMPTY_STRING;
		}

		Vector<String> quizzesVec, quizVec;

		String::Split(ROW_DATA_SEPARATOR, quizzesVec, s);

		for (size_t i = 0; i < quizzesVec.getSize(); i++)
		{			
			quizVec.clear();
			String quizString = quizzesVec[i];

			String::Split(QUIZ_ELEMENT_DATA_SEPARATOR, quizVec, quizString);

			if ( quizVec[4].StringToInt() == QuizStatus::NewQuiz || quizVec[4].StringToInt() == QuizStatus::EditQuiz)
			{
				String output = "[id " + quizVec[0] + "] " + quizVec[1] + " by " + quizVec[2];
				this->Writer().WriteLine(output);
			}
		}			
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
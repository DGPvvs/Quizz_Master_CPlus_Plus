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
/// Петод извеждащ функционалностите на Admin
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

void Admin::Action(const CommandStruct& cndStr)
{
	User::Action(cndStr);
}

String Admin::BuildUserData()
{
	String result = User::BuildUserData();
	return result;
}
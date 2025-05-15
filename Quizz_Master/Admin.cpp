#include "Admin.h"

Admin::Admin(IWriter* writer, IReader* reader, IBaseProvider* provider)
	: User::User(writer, reader, provider)
{
}

void Admin::Help()
{
	User::Help();

	std::cout << "pending" << std::endl;
	std::cout << "approve-quiz <quiz id>" << std::endl;
	std::cout << "approve-quiz <quiz id>" << std::endl;
	std::cout << "reject-quiz <quiz id> <reason>" << std::endl;
	std::cout << "view-reports" << std::endl;
	std::cout << "ban <username>" << std::endl;
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
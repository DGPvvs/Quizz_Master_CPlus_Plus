#include "Admin.h"


void Admin::Help()
{
	User::Help();
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
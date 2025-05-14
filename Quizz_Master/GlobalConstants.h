#ifndef Constants_H
#define Constants_H

#include "String.h"

enum ProviderOptions
{
	UserLoad,
	UserSave,
	UserFind,
	QuizzeLoad,
	QuizzeSave,
	ConfigSave,
	ConfigLoad,
};

enum UserOptions
{
	Empty			=	0b00000000,
	OK				=	0b00000001,
	NotFound		=	0b00000010,
	WrongPassword	=	0b00000100,
	AlreadyExisist	=	0b00001000,
	Ban				=	0b00010000,
};

const String CONFIG_FILE_NAME = "config.txt";
const String USERS_FILE_NAME = "users.txt";

const char FILENAME_TO_DATA_SEPARATOR = '$';

const String EXIT = "exit";
const String LOGIN = "login";
const String SIGNUP = "signup";
const String LOGOUT = "logout";
const String HELP = "help";

#endif

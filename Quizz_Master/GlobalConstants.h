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
	OK,
	Ban,
};

const String CONFIG_FILE_NAME = "config.txt";
const String USERS_FILE_NAME = "users.txt";

const char FILENAME_TO_DATA_SEPARATOR = '$';

const String EXIT = "exit";
const String LOGIN = "login";
const String SIGNUP = "signup";
const String LOGOUT = "logout";

#endif

#ifndef Constants_H
#define Constants_H

#include "String.h"

enum ProviderOptions
{
	UserLoad,
	UserSave,
	UserFind,
	NewUserSave,
	QuizzeLoad,
	QuizzeSave,
	ConfigSave,
	ConfigLoad,
};

enum UserOptions
{
	Empty			= 0b00000000,
	OK				= 0b00000001,
	NotFound		= 0b00000010,
	WrongPassword	= 0b00000100,
	AlreadyExisist	= 0b00001000,
	Ban				= 0b00010000,
	NewUserCreated	= 0b00100000,
};

enum QuestionType
{
	TF = 0,
	SC,
	MC,
	ShA,
	MP,
};

const String CONFIG_FILE_NAME = "config.txt";
const String USERS_FILE_NAME = "users.txt";

const char FILENAME_TO_DATA_SEPARATOR = '$';
const char ROW_DATA_SEPARATOR = '\n';
const char ELEMENT_DATA_SEPARATOR = ' ';
const char COMMA_DATA_SEPARATOR = ',';

const String EMPTY_STRING = "";
const String PROMPT_STRING = "> ";

const bool EXSIST = true;
const bool NOT_EXSIST = false;

const String EXIT = "exit";
const String LOGIN = "login";
const String SIGNUP = "signup";
const String LOGOUT = "logout";
const String HELP = "help";

const String BAN = "ban";

const String VIEW_PROFILE = "view-profile";
const String VIEW = "view";
const String CREATE_QUIZ = "create-quiz";

#endif

#ifndef Constants_H
#define Constants_H

#include "String.h"

enum ProviderOptions
{
	UserLoad,
	UserSave,
	QuizzeLoad,
	QuizzeSave,
	ConfigSave,
	ConfigLoad,
};

const char FILENAME_TO_DATA_SEPARATOR = '$';

const String EXIT = "exit";
const String LOGIN = "login";

#endif

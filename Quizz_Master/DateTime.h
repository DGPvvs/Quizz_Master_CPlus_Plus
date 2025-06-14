#ifndef DateTime_H
#define DateTime_H

#include <ctime> 

#include "String.h"

/// <summary>
/// Клас репрезентиращ работа с време - по настоящем само с текуща дата
/// </summary>

static class DateTime
{
public:
	static String DateNow();
};

#endif


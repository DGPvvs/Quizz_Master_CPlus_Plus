#ifndef CommandStruct_H
#define CommandStruct_H

#include "String.h"
/// <summary>
/// ��������� � ����� �� �������� ���������� �� ���������� �������
/// </summary>
struct CommandStruct
{
public:
	unsigned int paramRange;
	String command;
	String Param1;
	String Param2;
	String Param3;
	String Param4;
	String Param5;
	String CommandLine;
};

#endif // !CommandsStruct_H
#ifndef IQuestion_H
#define IQuestion_H

#include "String.h"

/// <summary>
/// ��������� ��������� ����������� �� ���������
/// </summary>

class IQuestion
{
public:
    virtual unsigned int Action() = 0;
    virtual void SetUpData(String&) = 0;
    virtual String BuildQuestionData() = 0;
    virtual String ToStringFile() = 0;
};

#endif // !IQuestion_H


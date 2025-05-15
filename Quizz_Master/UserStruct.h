#ifndef UserStruct_H
#define UserStruct_H

#include "String.h"

struct UserStruct
{
public:
    String userName;
    String fileName;
    String password;
    unsigned int id;
};

#endif
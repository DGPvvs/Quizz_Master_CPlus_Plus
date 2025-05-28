#ifndef Message_H
#define Message_H

#include "IBaseProvider.h"

class Message
{
private:
    IBaseProvider* provider;

public:
    Message(IBaseProvider*);
    String FindAllMessages();
};

#endif // !Message_H


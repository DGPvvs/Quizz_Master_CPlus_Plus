#ifndef Message_H
#define Message_H

#include "IBaseProvider.h"

class Message
{
private:
    IBaseProvider* provider;

    void SaveNewMessage(String&);
    void SaveMessage(String&);

public:
    Message(IBaseProvider*);
    String FindAllMessages(); 
    void SendMessage(String&);
};

#endif // !Message_H


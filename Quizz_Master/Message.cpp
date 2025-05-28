#include "Message.h"

Message::Message(IBaseProvider* provider)
    : provider(provider)
{
}

String Message::FindAllMessages()
{
    String s = MESSAGES_FILE_NAME;

    this->provider->Action(s, ProviderOptions::MessagesLoad);

    if (s == ERROR)
    {
        s = EMPTY_STRING;
    }

    return s;
}
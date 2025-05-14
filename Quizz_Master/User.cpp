#include "User.h"
#include "IBaseProvider.h"

unsigned int User::Hash(const String& str)
{
    unsigned int hash = 1315423911;

    for (std::size_t i = 0; i < str.getSize(); i++)
    {
        hash ^= ((hash << 5) + str[i] + (hash >> 2));
    }

    return (hash & 0x7FFFFFFF);
}

User::User(IWriter* writer, IReader* reader, IBaseProvider* provider)
    : writer(writer)
    , reader(reader)
    , provider(provider)
    , isHasLogin(false)
    , id(0u)
    , password(0)
{

}

String User::getName() const
{
    return this->firstName + " " + this->lastName;
}

String User::getUserName() const
{
    return this->userName;
}

unsigned int User::GetPassword() const
{
    return this->password;
}

void User::Login()
{

    if (!this->isHasLogin)
    {

    }

    //TODO
}

void User::Logout()
{
    //TODO
}

void User::Action(const CommandStruct& cmdStr)
{
    if (cmdStr.command == HELP)
    {
        this->Help();
    }

    //TODO
}

IWriter& User::Writer()
{
    return *writer;
}

IReader& User::Reader()
{
    return *reader;
}

bool User::GetIsHasLog()
{
    return this->isHasLogin;
}

void User::SetIsHasLog(bool isLogin)
{
    this->isHasLogin = isLogin;
}

void User::SetPassword(unsigned int password)
{
    this->password = password;
}

void User::Print()
{
    this->writer->WriteLine("I em User");
}

String User::BuildUserData()
{
    String result = "";

    result += "[" + this->id;
    result += "]";

    unsigned int id;

    String firstName;
    String lastName;
    String userName;

    unsigned int password;
    //TODO

    return result;
}

void User::Help()
{
    std::cout << "signup <first-name> <last-name> <username> <password1> <password2>" << std::endl;
    std::cout << "login <username> <password>" << std::endl;
    std::cout << "logout" << std::endl;
    std::cout << "help" << std::endl;
    std::cout << "exit" << std::endl;
}
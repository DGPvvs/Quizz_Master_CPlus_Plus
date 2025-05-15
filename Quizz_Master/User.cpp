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

void User::setFirstName(const String firstName)
{
    this->firstName = firstName;
}

void User::setLastName(const String lastName)
{
    this->lastName = lastName;
}

void User::setUserName(const String userName)
{
    this->userName = userName;
}

void User::setId(const unsigned int id)
{
    this->id = id;
}

unsigned int User::getId() const
{
    return this->id;
}

String User::getUserName() const
{
    return this->userName;
}

String User::getFileName() const
{
    return this->userFile;
}

void User::setFileName(const String fileName)
{
    this->userFile = fileName;
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

void User::AllUsers(String& users)
{
    this->provider->Action(users, ProviderOptions::UserFind);
}

int User::FindUserData(UserStruct& us, bool exsist)
{
    Vector<String> usersVec, v;
    String users;
    this->AllUsers(users);
    String::Split(ROW_DATA_SEPARATOR, usersVec, users);

    int userIndex = this->FindUserIndex(us, usersVec);

    if (userIndex > -1)
    {
        String user = usersVec[userIndex];
        String::Split(ELEMENT_DATA_SEPARATOR, v, user);
        if (exsist && this->Hash(us.password) != v[1].StringToInt())
        {
            return UserOptions::WrongPassword;
        }
        else if (exsist && v[4].StringToInt() == UserOptions::Ban)
        {
            return UserOptions::Ban;
        }

        us.fileName = v[2];
        us.id = v[3].StringToInt();

        return (UserOptions::Empty | UserOptions::OK | UserOptions::AlreadyExisist);
    }

    return UserOptions::NotFound;
}

int User::FindUserIndex(UserStruct& us, Vector<String>& usersVec)
{
    Vector<String> v;

    int result = -1;

    int i = 0;

    bool isLoopExit = false;
    bool isFound = false;
    bool notEmptyVector = usersVec.getSize() > 0;

    while (notEmptyVector && !(isLoopExit || isFound))
    {
        v.clear();
        String user = usersVec[i];
        String::Split(ELEMENT_DATA_SEPARATOR, v, user);

        if (us.userName == v[0])
        {
            isFound = true;
            result = i;
        }

        i++;

        if (i >= usersVec.getSize())
        {
            isLoopExit = true;
        }
    }

    return result;
}
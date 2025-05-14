#include <iostream>

#include "Game.h"
#include "User.h"
#include "Admin.h"
#include "GlobalConstants.h"

Game::Game(IWriter* writer, IReader* reader, IBaseProvider* provider)
    : writer(writer)
    , reader(reader)
    , provider(provider)
    , maxUserId(0)
    , maxQuizId(0)
{
}

void Game::Free()
{
    delete this->user;
    this->user = nullptr;
    delete this->command;
    this->command = nullptr;
}

Game::~Game()
{
    this->Free();
}

void Game::Init()
{
    this->command = new CommandStruct();
    this->user = new User(this->writer, this->reader, this->provider);
    this->LoadConfig();
}

void Game::Run()
{
    this->user->Print();
    this->GameLoop();
}

void Game::GameLoop()
{
    bool isLoopExit = false;

    while (!isLoopExit)
    {
        this->SetCommandStruct();

        if (this->command->command == EXIT)
        {
            isLoopExit = true;
            this->Exit();
        }
        else if (this->command->command == LOGIN)
        {
            this->LoginUser();
        }
        else if (this->command->command == LOGOUT)
        {
            if (this->user->GetIsHasLog())
            {
                this->LogoutUser();
            }
        }
        else if (this->command->command == SIGNUP)
        {
            this->SignupUser();
        }
        else
        {
            this->user->Action(*this->command);
        }

        //TODO
    }
}

void Game::SetCommandStruct()
{
    Vector<String> commandLine;
    this->command->command = "";

    String s = *reader->ReadLine();
    String::Split(' ', commandLine, s);

    if (commandLine.getSize() > 0)
    {
        this->command->command = commandLine[0];

        for (size_t i = commandLine.getSize(); i < 6; i++)
        {
            commandLine.push_back("");
        }

        this->command->Param1 = commandLine[1];
        this->command->Param2 = commandLine[2];
        this->command->Param3 = commandLine[3];
        this->command->Param4 = commandLine[4];
        this->command->Param5 = commandLine[5];
    }
}

void Game::Exit()
{
    if (this->user->GetIsHasLog())
    {
        this->LogoutUser();
    }

    this->SaveConfig();

    this->Free();
}

void Game::LoadConfig()
{
    Vector<String> v;
    String configString;
    this->provider->Action(configString, ProviderOptions::ConfigLoad);
    String::Split('\n', v, configString);

    this->maxUserId = v[0].StringToInt();
    this->maxQuizId = v[1].StringToInt();
}

void Game::SaveConfig()
{
    String configString = String::UIntToString(this->maxUserId) + "\n" + String::UIntToString(this->maxQuizId);

    this->provider->Action(configString, ProviderOptions::ConfigSave);
}

void Game::LoginUser()
{
    if (this->user->GetIsHasLog())
    {
        this->writer->WriteLine("You cannot log in a new user before logging out!");
        return;
    }

    UserStruct* us = new UserStruct();

    int uo = this->FindUser(*us);

    if (uo == UserOptions::NotFound)
    {
        this->writer->WriteLine("User not found!");
    }
    else if (uo == UserOptions::WrongPassword)
    {
        this->writer->WriteLine("Wrong password!");
    }
    else if (uo == UserOptions::Ban)
    {
        this->writer->WriteLine("Sorry, the user has been banned!");
    }
    else if ((uo & UserOptions::OK) == UserOptions::OK)
    {
        this->LoadUser(*us);
    }

    delete us;
    us = nullptr;
}

void Game::LogoutUser()
{
    //TODO - Записва се статуса на потребителя, ако не е админ
    delete this->user;
    this->user = nullptr;

    if (this->command->command != EXIT)
    {
        this->user = new User(this->writer, this->reader, this->provider);
    }
}

int Game::FindUser(UserStruct& us)
{
    Vector<String> v, vv;
    String users;
    this->provider->Action(users, ProviderOptions::UserFind);
    String::Split('\n', v, users);

    int i = 0;

    bool isLoopExit = false;
    bool isFound = false;

    while (!(isLoopExit || isFound))
    {
        vv.clear();
        String user = v[i];
        String::Split(' ', vv, user);

        if (this->command->Param1 == vv[0])
        {
            isFound = true;
        }

        i++;

        if (i >= v.getSize())
        {
            isLoopExit = true;
        }
    }

    if (isFound)
    {
        if (this->user->Hash(this->command->Param2) != vv[1].StringToInt())
        {
            return UserOptions::WrongPassword;
        }
        else if (vv[4].StringToInt() == UserOptions::Ban)
        {
            return UserOptions::Ban;
        }

        us.fileName = vv[2];
        us.id = vv[3].StringToInt();

        return (UserOptions::Empty | UserOptions::OK | UserOptions::AlreadyExisist);
    }

    return UserOptions::NotFound;
}

void Game::SignupUser()
{
    //TODO
}

void Game::SaveUser()
{
    //TODO
}

void Game::LoadUser(UserStruct& us)
{
    if (us.id <= 10)
    {
        delete this->user;
        this->user = nullptr;

        this->user = new Admin(this->writer, this->reader, this->provider);
        this->user->SetIsHasLog(true);
    }
    //TODO LoadPlayer
}
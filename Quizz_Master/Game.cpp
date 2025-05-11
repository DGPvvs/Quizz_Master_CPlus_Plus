#include <iostream>

#include "Game.h"
#include "User.h"
#include "GlobalConstants.h"

Game::Game(IWriter * writer, IReader * reader, IBaseProvider * provider)
    : writer(writer)
    , reader(reader)
    , provider(provider)
{
    this->command = new CommandStruct();
    this->user = new User(this->writer, this->reader);
    this->LoadConfig();
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
    this->user = new User(this->writer, this->reader);
    this->command = new CommandStruct();
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

        //TODO
    }
}

void Game::SetCommandStruct()
{
    Vector<String> commandLine;
    this->command->command = "";

    String s = *reader->ReadLine();
    s.Split(' ', commandLine);

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
        //TODO: Запис на данните за логнат играч
    }

    this->SaveConfig();

    this->Free();
}

void Game::LoadConfig()
{
    //TODO Четене на конфигурационни данни
}

void Game::SaveConfig()
{
    //TODO Запис на конфигурационни данни
}

void Game::LoginUser()
{
}

void Game::LogoutUser()
{
}

void Game::SignupUser()
{
}

void Game::SaveUser()
{
}

void Game::LoadUser()
{
}
// Quiz_Master_C_Plus_Plus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "String.h"
#include "ConsoleWriter.h"
#include "ConsoleReader.h"
#include "FileBaseProvider.h"
#include "Game.h"
#include "Vector.h"

    int main()
{
    String s = "Hello World";
    std::cout << s << std::endl;

    ConsoleWriter * writer = new ConsoleWriter();
    ConsoleReader* reader = new ConsoleReader();
    FileBaseProvider* provider = new FileBaseProvider();

    Game* game = new Game(writer, reader, provider);
    game->Init();
    game->Run();

    delete game;
    game = nullptr;

    delete writer;
    writer = nullptr;

    delete reader;
    reader = nullptr;

    delete provider;
    provider = nullptr;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

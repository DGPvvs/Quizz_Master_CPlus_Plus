#include "FileBaseProvider.h"

void FileBaseProvider::FileSave(String& str)
{
    Vector<String> v;
    String::Split(FILENAME_TO_DATA_SEPARATOR, v, str);
    std::ofstream ofs;

    ofs.open(v[0].c_str(), std::fstream::out | std::fstream::trunc);
    if (ofs.is_open())
    {
        for (int i = 0; i < v[1].getSize(); ++i)
        {
            ofs.put(v[1][i]);
        }

        ofs.close();
    }
}

void FileBaseProvider::FileLoad(String& str)
{
    std::ifstream ifs;
    char* arr = new char[1024] {'\0'};


    ifs.open(str.c_str());

    str = "";

    if (!ifs.is_open())
    {
        std::cerr << "Error opening the file!";
        str = "error";
    }

    while (!(ifs.eof() || ifs.fail()))
    {
        ifs.getline(arr, 1024);
        str += String(arr) + String("\n");
    }

    ifs.close();

    std::cout << str << std::endl;

    delete[] arr;
}

void FileBaseProvider::FileDelete(String& str, ProviderOptions options)
{
	//TODO
}

void FileBaseProvider::Action(String& str, ProviderOptions options)
{
    if (options == ProviderOptions::ConfigLoad)
    {
        str = CONFIG_FILE_NAME;
        FileLoad(str);
    }
    else if (options == ProviderOptions::ConfigSave)
    {
        char* arr = new char[2] {'\0'};
        arr[0] = FILENAME_TO_DATA_SEPARATOR;
        String s = CONFIG_FILE_NAME + String(arr) + str;
        FileSave(s);

        delete[] arr;
        arr = nullptr;
    }
}
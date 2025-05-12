#include "FileBaseProvider.h"

void FileBaseProvider::FileSave(String& str)
{
    Vector<String> v;
    str.Split(FILENAME_TO_DATA_SEPARATOR, v);
    std::ofstream ofs;

    ofs.open(v[0].c_str(), std::fstream::out | std::fstream::trunc);
    if (ofs.is_open())
    {
        ofs << v[1];
        ofs.close();
    }
}

String FileBaseProvider::FileLoad(String str)
{
	
    std::ifstream ifs;
    char* arr = new char[1024] {'\0'};
    String s = "";

    ifs.open(str.c_str());

    if (!ifs.is_open())
    {
        std::cerr << "Error opening the file!";
        return "error";
    }

    while (!(ifs.eof() || ifs.fail()))
    {
        ifs.get(arr, 1024);
        s += String(arr) + String(" ");
        ifs.ignore();
    }

    ifs.close();

    delete[] arr;
    return s;
}

void FileBaseProvider::FileDelete(String& str, ProviderOptions options)
{
	//TODO
}

void FileBaseProvider::Action(String& str, ProviderOptions options)
{
    if (options == ProviderOptions::ConfigLoad)
    {
        String s = "config.txt";
        str = this->FileLoad(s);
    }
    else if (options == ProviderOptions::ConfigSave)
    {
        char* arr = new char[2] {'\0'};
        arr[0] = FILENAME_TO_DATA_SEPARATOR;
        String s = "config.txt" + String(arr) + str;
        this->FileSave(s);

        delete[] arr;
        arr = nullptr;
    }
}
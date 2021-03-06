// HW5.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <string>

using namespace std;

class FileReader
{
public:
    FileReader(string filename)
    {
        fileStream = new ifstream(filename);
        if (!fileStream->good())
        {
            throw invalid_argument("couldn't open file");
        }
    };
    ~FileReader()
    {
        delete fileStream;
    };

    bool GetNextWord(string &word)
    {
        while (true)
        {
            // try to read the next word from the current line
            char *next = strtok_s((strtokContext == nullptr) ? currentLine : nullptr,
                                  " \t.,:;!?\"",
                                  &strtokContext);
            if (next != nullptr)
            {
                word.assign(next);
                return true;
            }
            else
            {
                *currentLine = '\0';
                strtokContext = nullptr;
            }

            string nextLine;
            getline(*fileStream, nextLine);
            if (!fileStream->good())
            {
                return false;
            }

            strcpy_s(currentLine, nextLine.c_str());
            for (unsigned int i = 0; currentLine[i] != '\0'; i++)
            {
                currentLine[i] = tolower(currentLine[i]);
            }
        }

        return false;
    }

private:
    ifstream *fileStream = nullptr;
    char currentLine[256] = {};
    char *strtokContext = nullptr;
};

int main()
{
    FileReader fr = FileReader("c:\\users\\billdon\\desktop\\input.txt");
    string word;

    while (fr.GetNextWord(word))
    {
        cout << word << endl;
    }

    cout << "press enter to exit";
    getc(stdin);
    return 0;
}


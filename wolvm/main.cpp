#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const string version = "1.0.0.0"; //need for future frameworks
const string info = "World of Legends Virtual Machine Native\nVersion: " + version + "\nAuthors: snaulX, kosta2222";
int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        cout << info ;
    }
    else
    {
        if (argv[1] == "-info")
        {
                cout << info ;
        }
        else
        {
            ifstream input(argv[1]); //open get file
            string code = "", line;
            if (input.is_open())
            {
                while (getline(input, line))
                {
                   code += line; //add line of file to code
                }
            }
            input.close();     // close file
        }
    }
    return 0;
}

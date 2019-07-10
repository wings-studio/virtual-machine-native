/*
 * File:   main.cc
 * author:M.K.K
 * Created on 10 июля 2019 г., 15:17
 * C++11
 */

#include <cstdlib>

#include <vector>
#include <string.h>

#include <fstream>

#include <iostream>

using namespace std;

class langClass
{
};

class langFunction
{
};

class langValue
{
};

class Stack
{
public:

  Stack () { }

};

class Vm
{
private:
  vector <string> coVector;
public:

  void
  initBaseTypes () { }

  void
  initCodeVector (vector <string> _coVector)
  {
    coVector = _coVector;
  }

  void
  execute ()
  {
    int position = 0;

    //----------------------------
    Stack *stack = new Stack ();
    //----------------------------

    string tWord = "";

    bool isVmWorks = true;
    while (isVmWorks)
      {
        tWord = coVector[position];

        if (!strcmp ("_loads", tWord.c_str ()))
          {
          }
        else if (!strcmp ("stack", tWord.c_str ()))
          {
          }
        else if (!strcmp ("end", tWord.c_str ()))
          {
            break;
          }
        else if (!strcmp ("}", tWord.c_str ()))
          {
            position++;
          }
        else if (!strcmp ("{", tWord.c_str ()))
          {

          }
        else
          {
            cout << "Unknown keyword " << tWord << " at position: " << position << endl;
            exit (1);
          }
        position++;
      }
  }

  Stack
  parse (string _stack_code) { }

};


//========================

int
main (int argc, char** argv)
{
  if (argc == 1)
    {
      cout << "World of Legends Virtual Machine version 0.1.0 author Arkadiy Vitalyev." << endl;
      exit (2);
    }

  char* progrFileNam = argv[1];
  // считываем весь файл в переменную, потом  разбить на токены в mainCoVector

  ifstream inf;
  string progrText;
  inf.open (progrFileNam);
  getline (inf, progrText, '\0');
  cout << progrText << endl;
  inf.close ();

  vector<string> mainCoVector = {"stack", "{", "}", "end"};

  Vm * vm = new Vm ();
  vm->initBaseTypes ();
  vm->initCodeVector (mainCoVector);
  vm->execute ();

  return 0;
}
//=========================


/* 
 * File:   main_app.cpp
 * Author: papa
 *
 * Created on 23 февраля 2020 г., 6:58
 */
#include <string.h>
#include "utilMacr.h"
#include "SB.h"
#include "Value.h"
#include "wolFunction.h"
#include "wolClass.h"
#include "Stack.h"
#include "VirtualMachine.h"
/*(!)
 * рус: Основная идея, выполнение промежуточного текстового языка так называемого
 * ITLWM(Intermediate text language of Wol Vm)
 * en: The main idea is execution of intermidiate text language as we call ITLWM(Intermediate text language of Wol Vm)
 * 
 */
using namespace std;
S GIT_BR = "new_TestCSharpClasseAsCpp_branch"; // ветка Git | git branch
S GIT_HASH = "6b3261b40b8b776e662b63a72309cf914649b1f9"; // хэш коммита | commit hash
const string version = "1.0.0.0"; // нужно для следующих фреймворков | need for future frameworks
const string info = "World of Legends Virtual Machine Native\nVersion: " + version + "\nAuthors Alexander Gunge, Muhamedjanov Konstantin  K."+" ["+GIT_BR+" "+GIT_HASH+"]"; //need for future frameworks
const string help = "World of Legends Virtual Machine v" + version + " Helper\n" ++"\nArguments:\n";
/**
 * рус: В основном должен принимать текстовый файл программы - ITLWM(Intermediate text language of Wol Vm)
 * en: mainly accept text file of program - ITLWM(Intermediate text language of Wol Vm)
 * @param argc - количество аргументов | amount of arguments
 * @param argv - вектор строк | vector of strings
 * @return - код успеха | success code
 */
wolClass wolClass_o;
wolFunction wolFunction_o;
Value value;
Stack stack();
StringBuilder buffer;
VirtualMachine VirtualMachine;
int main(int argc, char* argv[]) {
	if (argc == 1)
		cout << info;
	else $
		if (!strcmp(argv[1], "-info"))
		cout << info;
	        else if (!strcmp(argv[1], "-help") || !strcmp(argv[1], "--help"))
		   cout << help,
		   cout << "Usage: <exe> <itlwm_text_file>.bld" << endl;
	        else if (!strcmp(argv[1], "-encode"))
		   cout << "Sorry, while this option is this version in develop";
	        else $
		      ifstream input(argv[1]); //открываем файл | open get file
	              S code = "", line;
	              if (input.is_open())$
		         while (getline(input, line))
			      code += line; //добавляем строку к коду|add line of file to code
	                      $$
	              input.close(); // закрываем файл | close file
	              $$
	              $$
	_0_("main");
}

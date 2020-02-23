/* 
 * File:   main.cpp
 * Author: papa
 *
 * Created on 21 февраля 2020 г., 7:27
 */
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <stdbool.h>
#include <string.h>
#include "utilMacr.h"
#include "SB.h"
/*(!)
 * рус: Основная идея, выполнение промежуточного текстового языка так называемого
 * ITLWM(Intermediate text language of Wol Vm)
 * en: The main idea is execution of intermidiate text language as we call ITLWM(Intermediate text language of Wol Vm)
 * 
 */
using namespace std;
const string version = "1.0.0.0"; //need for future frameworks
const string info = "World of Legends Virtual Machine Native\nVersion: " + version + "\nAuthors Alexander Gunge, Muhamedjanov Konstantin  K."; //need for future frameworks
const string help = "World of Legends Virtual Machine v" + version + " Helper\n" +
	+"\nArguments:\n";
S GIT_BR = ""; // ветка Git | git branch
S GIT_HASH = ""; // хэш коммита | commit hash
void Run(string input);
typedef enum  {
	//this type throws when ...
	TypeNotSupportedException, //... when in enum init method and etc.
	StackOverflowException, //... size of stack is bigger then memory
	InvalidTypeException, //... get type doesn`t fits
	NotFoundException, //... 'anything' not found
	InitilizateException, //... problems made on initilization
	BLDSyntaxException, //... wrong syntax of build-file
	LoadsException, //... framework can`t load or other troubles with him
	FileNotFoundException, //... file not found
	ArgumentsNullException, //... argument have 'null'
	IndexOutOfRangeException, //... get index who bigger than length of collection
	NullRefrenceException, //... operation work with 'null'
	ChildException, //... class or functions hasn`t child
	SecurityException, //... call private property
	ArgumentsOutOfRangeException, //... arguments bigger or lower than need
	NumberFormatException, //... parsing not valid string (to any number)
	FormatException, //... parsing not valid string (to any type)
	ValueException //... value call with parents or any more
}ExceptionType;
void ThrowVMException(string message, int position, ExceptionType type);
/**
 * рус: В основном должен принимать текстовый файл программы - ITLWM(Intermediate text language of Wol Vm)
 * en: mainly accept text file of program - ITLWM(Intermediate text language of Wol Vm)
 * @param argc - количество аргументов | amount of arguments
 * @param argv - вектор строк | vector of strings
 * @return - код успеха | success code
 */
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
class Stack {
};
/* рус: Метод где мы анализиреум исходный код ITLWM(Intermediate text language
 * of Wol Vm), создаем оььекты на стеке.
 * en: Methon where we parse(analize) source of ITLWM(Intermediate text language
 * of Wol Vm), create objects on stack.
 */
/**
 * Выполнение
 * Execution
 * @param input исходный код itlwm типа строки | source code of itlwm as string
 */


void Run(S input) {
	StringBuilder buffer;
	//main cycle
	I position = 0;
	char current = input[0];
	bool test = true;
	while (position < input.size())
	{
		while (current == ' ') //skip whitespaces
		{
			position++;
			if (position > input.size())
			{
				ThrowVMException("Build-file have only whitespaces", position, BLDSyntaxException);
				return;
			}
			current = input[position];
		}
		while (current != ' ') //get word
		{
			buffer.Append(current);
			position++;
			try
			{
				if (position > input.size())
					throw runtime_error("");
				current = input[position];
			} catch (exception& ex)
			{
				ThrowVMException("Build-file have only one word", position, BLDSyntaxException);
				return;
			}
		}
		buffer.Terminate();
		if (!strcmp(buffer.ToString(), "_loads"))
		{
			buffer.Clear();
			while (current == ' ')
			{
				position++;
				if (position > input.size())
				{
					ThrowVMException("Start of loads struct not found", position, BLDSyntaxException);
					return;
				}
				current = input[position];
			}
			if (current == '{')
			{
				buffer.Clear();
				while (current != '}') //get loads body
				{
					buffer.Append(current);
					position++;
					if (position > input.size())
					{
						ThrowVMException("End of loads struct not found", position, BLDSyntaxException);
						return;
					}
					current = input[position];
				}
				buffer.RemoveFirst();
				//start parse loads
				l* dllSource = buffer.ToString();
				/*
				Type mainType = typeof(VMLibrary);
				List<string> dllNames = dllSource.Split(';').ToList();
				foreach(string dllName in dllNames) {
					Assembly assembly = null;
					string full_path = AppDomain.CurrentDomain.BaseDirectory + dllName.Trim() + ".dll";
					try
					{
						assembly = Assembly.LoadFrom(full_path);
					} catch (exception& ex)
					{
						ThrowVMException("Library with info {full_path} not found.\n{ex.Message}", position, ExceptionType.FileNotFoundException);
						break;
					}
					Type mainClass = assembly.GetTypes().FirstOrDefault(t = > t != mainType && mainType.IsAssignableFrom(t));
					if (test)
					{
						cout<<("Framework Info: " + assembly);
						cout<<("Full path to framework: " + full_path);
						cout<<(string.Join<Type>(' ', assembly.GetTypes()));
					}
					if (mainClass != null)
					{
						if (Activator.CreateInstance(mainClass) is VMLibrary mainObj) mainObj.Load();
						else ThrowVMException("Main class in library by name {dllName} haven`t type VMLibrary and will cannot loaded", position, ExceptionType.LoadsException);
					} else
					{
						ThrowVMException("Library by name {dllName} haven`t main class and will cannot loaded", position, ExceptionType.LoadsException);
					}
				}*/
				//end parse loads
			} else
			{
				ThrowVMException("Start of loads struct not found", position, BLDSyntaxException);
			}
		} else if (!strcmp(buffer.ToString(), "stack"))
		{
			buffer.Clear();
			while (current == ' ')
			{
				position++;
				if (position > input.size())
				{
					ThrowVMException("Start of stack not found", position, BLDSyntaxException);
					return;
				}
				current = input[position];
			}
			if (current == '{')
			{
cycle:
				while (current != '}') //get stack body
				{
					buffer.Append(current);
					position++;
					if (position > input.size())
					{
						ThrowVMException("End of stack not found", position, BLDSyntaxException);
						return;
					}
					current = input[position];
				}
				if (input[++position] == ';')
				{
					buffer.Append(current);
					current = input[position];
					goto cycle;
				}
				//				mainstack.Add(Stack.Parse(buffer.ToString().Trim()));
			} else
			{
				ThrowVMException("Start of stack not found", position, BLDSyntaxException);
			}
			position--;
		} else if (!strcmp(buffer.ToString(), "main"))
		{
			buffer.Clear();
			while (current == ' ')
			{
				position++;
				if (position > input.size())
				{
					ThrowVMException("Start of script not found", position, BLDSyntaxException);
					return;
				}
				current = input[position];
			}
			if (current == '{')
			{
				while (current != '}') //get script
				{
					buffer.Append(current);
					position++;
					if (position > input.size())
					{
						ThrowVMException("End of script not found", position, BLDSyntaxException);
						return;
					}
					current = input[position];
				}
				//				Script.Parse(buffer.ToString().Trim().Remove(0, 1));
			} else
			{
				ThrowVMException("Start of script not found", position, BLDSyntaxException);
			}
		} else if (!strcmp(buffer.ToString(), "end"))
		{
			if (test)
			{
				//test stack
				cout << ("Info about program in the end.\nMain stack:");
				//				cout<<(mainstack.ToString());
				cout << ("Expressions:");
				//				foreach(string expr_name in expressions.Keys) {
				//					cout<<(expr_name);
				//				}
				cout << ("Time of program: {Environment.TickCount - time}");
			}
			return;
		} else if (!strcmp("}", buffer.ToString()))
		{
			position++;
			continue;
		} else
		{
			ThrowVMException("Unknown keyword {buffer.ToString()}", position, BLDSyntaxException);
		}
	}
}
void ThrowVMException(string message, int position, ExceptionType type) {
	cout <<type<< "Exception in position{" << position << "}" << message << endl;
}

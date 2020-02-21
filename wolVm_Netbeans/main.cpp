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
void Run(string input);

class StringBuilder {
public :
	c buff[10];
	I ind;
	StringBuilder() {
		ind = 0;
	}
	v Append(c char_) {
		buff[ind] = char_;
		ind++;
	}
	c * ToString() {
		return buff;
	}
	v Clear() {
		ind = 0;
	}
	v Terminate(){
		buff[ind+1]='\0';
	}
	v Remove(I b,I e){
		for (int b = 0; b < e; b++);
			//buff[b]=''; // ошибка
	}
	c* Trim(){// удаляет пробелы | delete whitespaces
		for (int i = 0; i < ind; i++)
			if(buff[i]==' ');
				//buff[i]=''; // ошибка
		return buff;
		
					
	}
};

void ThrowVMException(string message, int position, I type);
/**
 * рус: В основном должен принимать текстовый файл программы - ITLWM(Intermediate text language of Wol Vm)
 * en: mainly accept text file of program - ITLWM(Intermediate text language of Wol Vm)
 * @param argc - количество аргументов | amount of arguments
 * @param argv - вектор строк | vector of strings
 * @return - код успеха | success code
 */
#define buf_for_itlwm_keyword 10
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
StringBuilder buffer;
void Run( S input) {
	;
	;
	//main cycle
	I position = 0;
	char current = input[0];
	bool test=true;
	while (position < input.size())
	{
		while (current==' ') //skip whitespaces
		{
			position++;
			if (position > input.size())
			{
				ThrowVMException("Build-file have only whitespaces", position, 0);
				return;
			}
			current = input[position];
		}
		while (current!=' ') //get word
		{
			buffer.Append(current);
			position++;
			try
			{
				current = input[position];
				if (position > input.size() )
					throw   runtime_error("");
			} catch (exception& ex)
			{
				ThrowVMException("Build-file have only one word", position, 0);
				return;
			}
		}
		buffer.Terminate();
		if (!strcmp(buffer.ToString(),"_loads") )
		{
			buffer.Clear();
			while (current==' ')
			{
				position++;
				if (position > input.size())
				{
					ThrowVMException("Start of loads struct not found", position, 0);
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
						ThrowVMException("End of loads struct not found", position, 0);
						return;
					}
					current = input[position];
				}
				buffer.Remove(0, 1);
				//start parse loads
				c* dllSource = buffer.ToString();
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
				ThrowVMException("Start of loads struct not found", position, 0);
			}
		} else if (!strcmp(buffer.ToString(),"stack") )
		{
			buffer.Clear();
			while (current==' ')
			{
				position++;
				if (position > input.size())
				{
					ThrowVMException("Start of stack not found", position, 0);
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
						ThrowVMException("End of stack not found", position, 0);
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
				ThrowVMException("Start of stack not found", position, 0);
			}
			position--;
		} else if (!strcmp(buffer.ToString(), "main"))
		{
			buffer.Clear();
			while (current==' ')
			{
				position++;
				if (position > input.size())
				{
					ThrowVMException("Start of script not found", position, 0);
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
						ThrowVMException("End of script not found", position, 0);
						return;
					}
					current = input[position];
				}
//				Script.Parse(buffer.ToString().Trim().Remove(0, 1));
			} else
			{
				ThrowVMException("Start of script not found", position, 0);
			}
		} else if (!strcmp(buffer.ToString(),"end") )
		{
			if (test)
			{
				//test stack
				cout<<("Info about program in the end.\nMain stack:");
//				cout<<(mainstack.ToString());
				cout<<("Expressions:");
//				foreach(string expr_name in expressions.Keys) {
//					cout<<(expr_name);
//				}
				cout<<("Time of program: {Environment.TickCount - time}");
			}
			return;
		} else if (!strcmp("}", buffer.ToString()) )
		{
			position++;
			continue;
		} else
		{
			ThrowVMException("Unknown keyword {buffer.ToString()}", position, 0);
		}
	}
}
void ThrowVMException(string message, int position, I type) {
	cout << "Exception in position{" << position << "}" << message << endl;
}

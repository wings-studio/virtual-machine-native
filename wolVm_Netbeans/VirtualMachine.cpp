/* 
 * File:   main.cpp
 * Author: papa
 *
 * Created on 21 февраля 2020 г., 7:27
 */
#include <iostream>
#include <cstring>
#include "Stack.h"
#include "Enums.h"
#include "utilMacr.h"
#include "SB.h"
using namespace std;
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
extern StringBuilder buffer;
void VirtualMachine::ThrowVMException(string message, int position, ExceptionType type) {
	cout <<type<< "Exception in position{" << position << "}" << message << endl;
} 
void VirtualMachine::Run(S input) {
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
				this->ThrowVMException("Build-file have only whitespaces", position, BLDSyntaxException);
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
				this->ThrowVMException("Build-file have only one word", position, BLDSyntaxException);
				return;
			}
		}
		if (!strcmp(buffer.ToString(), "_loads"))
		{
			buffer.Clear();
			while (current == ' ')
			{
				position++;
				if (position > input.size())
				{
					this->ThrowVMException("Start of loads struct not found", position, BLDSyntaxException);
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
						this->ThrowVMException("End of loads struct not found", position, BLDSyntaxException);
						return;
					}
					current = input[position];
				}
				buffer.Trim();
				buffer.Remove(0,1);
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
						this->ThrowVMException("Library with info {full_path} not found.\n{ex.Message}", position, ExceptionType.FileNotFoundException);
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
						else this->ThrowVMException("Main class in library by name {dllName} haven`t type VMLibrary and will cannot loaded", position, ExceptionType.LoadsException);
					} else
					{
						this->ThrowVMException("Library by name {dllName} haven`t main class and will cannot loaded", position, ExceptionType.LoadsException);
					}
				}*/
				//end parse loads
			} else
			{
				this->ThrowVMException("Start of loads struct not found", position, BLDSyntaxException);
			}
		} else if (!strcmp(buffer.ToString(), "stack"))
		{
			buffer.Clear();
			while (current == ' ')
			{
				position++;
				if (position > input.size())
				{
					this->ThrowVMException("Start of stack not found", position, BLDSyntaxException);
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
						this->ThrowVMException("End of stack not found", position, BLDSyntaxException);
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
				this->ThrowVMException("Start of stack not found", position, BLDSyntaxException);
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
					this->ThrowVMException("Start of script not found", position, BLDSyntaxException);
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
						this->ThrowVMException("End of script not found", position, BLDSyntaxException);
						return;
					}
					current = input[position];
				}
				//				Script.Parse(buffer.ToString().Trim().Remove(0, 1));
			} else
			{
				this->ThrowVMException("Start of script not found", position, BLDSyntaxException);
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
			this->ThrowVMException("Unknown keyword {buffer.ToString()}", position, BLDSyntaxException);
		}
	}
}
void testRun() {
	string input1 = "_loads { wolSystem }";
	Run(input1);
	if (true /*check result*/)
	{
		std::cout << "%TEST_FAILED% time=0 testname=testRun (run) message=error message sample" << std::endl;
	}
}

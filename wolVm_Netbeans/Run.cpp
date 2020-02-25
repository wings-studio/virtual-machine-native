/* 
 * File:   main.cpp
 * Author: papa
 *
 * Created on 21 февраля 2020 г., 7:27
 */
#include <iostream>
#include <cstring>
#include "hedVm.h"
#include "utilMacr.h"
#include "SB.h"
using namespace std;
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
extern StringBuilder buffer;
I VM_position=0;
void Run(S input) {
	//main cycle
//	I VM_position = 0;
	char current = input[0];
	bool test = true;
	while (VM_position < input.size())
	{
		while (current == ' ') //skip whitespaces
		{
			VM_position++;
			if (VM_position > input.size())
			{
				ThrowVMException("Build-file have only whitespaces", VM_position, BLDSyntaxException);
				return;
			}
			current = input[VM_position];
		}
		while (current != ' ') //get word
		{
			buffer.Append(current);
			VM_position++;
			try
			{
				if (VM_position > input.size())
					throw runtime_error("");
				current = input[VM_position];
			} catch (exception& ex)
			{
				ThrowVMException("Build-file have only one word", VM_position, BLDSyntaxException);
				return;
			}
		}
		if (!strcmp(buffer.ToString(), "_loads"))
		{
			buffer.Clear();
			while (current == ' ')
			{
				VM_position++;
				if (VM_position > input.size())
				{
					ThrowVMException("Start of loads struct not found", VM_position, BLDSyntaxException);
					return;
				}
				current = input[VM_position];
			}
			if (current == '{')
			{
				buffer.Clear();
				while (current != '}') //get loads body
				{
					buffer.Append(current);
					VM_position++;
					if (VM_position > input.size())
					{
						ThrowVMException("End of loads struct not found", VM_position, BLDSyntaxException);
						return;
					}
					current = input[VM_position];
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
						ThrowVMException("Library with info {full_path} not found.\n{ex.Message}", VM_position, ExceptionType.FileNotFoundException);
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
						else ThrowVMException("Main class in library by name {dllName} haven`t type VMLibrary and will cannot loaded", VM_position, ExceptionType.LoadsException);
					} else
					{
						ThrowVMException("Library by name {dllName} haven`t main class and will cannot loaded", VM_position, ExceptionType.LoadsException);
					}
				}*/
				//end parse loads
			} else
			{
				ThrowVMException("Start of loads struct not found", VM_position, BLDSyntaxException);
			}
		} else if (!strcmp(buffer.ToString(), "stack"))
		{
			buffer.Clear();
			while (current == ' ')
			{
				VM_position++;
				if (VM_position > input.size())
				{
					ThrowVMException("Start of stack not found", VM_position, BLDSyntaxException);
					return;
				}
				current = input[VM_position];
			}
			if (current == '{')
			{
cycle:
				while (current != '}') //get stack body
				{
					buffer.Append(current);
					VM_position++;
					if (VM_position > input.size())
					{
						ThrowVMException("End of stack not found", VM_position, BLDSyntaxException);
						return;
					}
					current = input[VM_position];
				}
				if (input[++VM_position] == ';')
				{
					buffer.Append(current);
					current = input[VM_position];
					goto cycle;
				}
				//				mainstack.Add(Stack.Parse(buffer.ToString().Trim()));
			} else
			{
				ThrowVMException("Start of stack not found", VM_position, BLDSyntaxException);
			}
			VM_position--;
		} else if (!strcmp(buffer.ToString(), "main"))
		{
			buffer.Clear();
			while (current == ' ')
			{
				VM_position++;
				if (VM_position > input.size())
				{
					ThrowVMException("Start of script not found", VM_position, BLDSyntaxException);
					return;
				}
				current = input[VM_position];
			}
			if (current == '{')
			{
				while (current != '}') //get script
				{
					buffer.Append(current);
					VM_position++;
					if (VM_position > input.size())
					{
						ThrowVMException("End of script not found", VM_position, BLDSyntaxException);
						return;
					}
					current = input[VM_position];
				}
				//				Script.Parse(buffer.ToString().Trim().Remove(0, 1));
			} else
			{
				ThrowVMException("Start of script not found", VM_position, BLDSyntaxException);
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
			VM_position++;
			continue;
		} else
		{
			ThrowVMException("Unknown keyword {buffer.ToString()}", VM_position, BLDSyntaxException);
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

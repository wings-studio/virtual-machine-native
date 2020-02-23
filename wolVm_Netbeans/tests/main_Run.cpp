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

StringBuilder::StringBuilder() {
	ind = 0;
}

v StringBuilder::Append(l char_) {
	buff[ind] = char_;
	ind++;
}

l * StringBuilder::ToString() {
	return buff;
}

v StringBuilder::Clear() {
	ind = 0;
}

v StringBuilder::Terminate() {
	buff[ind + 1] = '\0';
}

l* StringBuilder::RemoveFirst() {
	strcpy(buff_n, (char*) (&this->ToString()[1]));
	strcpy(buff, buff_n);
	return buff_n;
}

l* StringBuilder::Trim() {// удаляет пробелы | delete whitespaces
	I ws_cn_before = 0;
	I le_cn = 0;
	I count_where_beg_ri_ws = 0;
	I pos = 0;
	for (int i = 0; i<this->Len(); i++)
		if (buff[i] == ' ')
			ws_cn_before += 1;
		else
			break;
	for (int i = 0; i<this->Len(); i++)
		if (buff[i] != ' ')
			le_cn++;
	count_where_beg_ri_ws = ws_cn_before + le_cn;
	for (int i = ws_cn_before; i < count_where_beg_ri_ws; i++)
		buff_n[pos] = buff[i],
		pos++;
	//--------------------------------------------------------------------------
	return buff_n;
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
S test_a[10];

v add_t(S str_) {
	static I pos = 0;
	test_a[pos] = str_;
}

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

void testRun() {
	string input1 = "_loads { wolSystem }";


	Run(input1);
	if (true /*check result*/)
	{
		std::cout << "%TEST_FAILED% time=0 testname=testRun (run) message=error message sample" << std::endl;
	}
}

void ThrowVMException(string message, int position, ExceptionType type) {
	cout << type << "Exception in position{" << position << "}" << message << endl;
}

int main(int argc, char** argv) {
	std::cout << "%SUITE_STARTING% run" << std::endl;
	std::cout << "%SUITE_STARTED%" << std::endl;

	std::cout << "%TEST_STARTED% testRun (run)" << std::endl;
	testRun();
	std::cout << "%TEST_FINISHED% time=0 testRun (run)" << std::endl;

	std::cout << "%SUITE_FINISHED% time=0" << std::endl;

	return(EXIT_SUCCESS);
}


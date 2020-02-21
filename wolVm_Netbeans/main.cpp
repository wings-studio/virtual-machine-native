/* 
 * File:   main.cpp
 * Author: papa
 *
 * Created on 21 февраля 2020 г., 7:27
 */

#include <iostream>
#include <string>
#include <fstream>
#include "utilMacr.h"

using namespace std;

const string version = "1.0.0.0"; //need for future frameworks
const string info = "World of Legends Virtual Machine Native\nVersion: " + version + "\nAuthors: snaulX, kosta2222"; //need for future frameworks
const string help = "World of Legends Virtual Machine v" + version + " Helper\n" +
	+"\nArguments:\n";
void Run(string input);
int main(int argc, char* argv[]) {
	if (argc == 1)
	{
		cout << info;
	} else
	{
		if (!strcmp(argv[1], "-info"))
		{
			cout << info;
		} else if (!strcmp(argv[1], "-help") || !strcmp(argv[1], "--help"))
		{
			cout << help;
		} else if (!strcmp(argv[1], "-encode"))
		{
			cout << "Sorry, while this option is this version in develop";
		} else
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
			input.close(); // close file
		}
	}
	return 0;
}
class Stack{
	
};
void Run(Stack *mainstack,string input) {
	/* Скопирова sharp
	 */
	//add base classes to stack                 parents:
	mainstack->classes.Add("void", new Void()); //no
	mainstack->classes.Add("byte", new wolByte()); //void
	mainstack->classes.Add("short", new wolShort()); //byte
	mainstack->classes.Add("string", new wolString()); //void
	mainstack->classes.Add("int", new wolInt()); //short
	mainstack->classes.Add("float", new wolFloat()); //int
	mainstack->classes.Add("long", new wolLong()); //int
	mainstack->classes.Add("double", new wolDouble()); //float
	mainstack->classes.Add("Type", new wolType()); //void
	mainstack->classes.Add("Func", new wolFunc()); //void
	mainstack->classes.Add("Enum", new wolEnum()); //void
	mainstack->classes.Add("char", new wolChar()); //void
	mainstack->classes.Add("Block", new wolBlock()); //void
	mainstack->classes.Add("Collection", new wolCollection()); //void
	mainstack->classes.Add("Array", new wolArray()); //Collection
	mainstack->classes.Add("Link", new wolLink()); //void
	mainstack->classes.Add("bool", new wolBool()); //void

	//main cycle
	int position;
	char current;
	position = 0;
	current = input[0];
	int time = Environment.TickCount;
	// парсим весь исходный код
	while (position < input.size())$
	
		while (current==' ')$ //skip whitespaces
		
			position++;
			if (position > input.size())
			{
				cout<<("Build-file have only whitespaces", position, ExceptionType.BLDSyntaxException);
				return;
			}
			current = input[position];
		        $$ 
		StringBuilder buffer = new StringBuilder();
		while (!char.IsWhiteSpace(current)) //get word
		{
			buffer.Append(current);
			position++;
			try
			{
				current = input[position];
			} catch (IndexOutOfRangeException)
			{
				cout<<"Build-file have only one word"<< position<< ExceptionType.BLDSyntaxException;
				return;
			}
		}
		if (buffer.ToString() == "_loads")
		{
			buffer.Clear();
			while (char.IsWhiteSpace(current))
			{
				position++;
				if (position > input.Length)
				{
					cout<<"Start of loads struct not found"<<position<< ExceptionType.BLDSyntaxException;
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
					if (position > input.Length)
					{
						cout<<"End of loads struct not found"<< position, ExceptionType.BLDSyntaxException);
						return;
					}
					current = input[position];
				}
				buffer.Remove(0, 1);
				//start parse loads
				string dllSource = buffer.ToString();
				Type mainType = typeof(VMLibrary);
				List<string> dllNames = dllSource.Split(';').ToList();

				foreach(string dllName in dllNames) {
					Assembly assembly = null;
					string full_path = AppDomain.CurrentDomain.BaseDirectory + dllName.Trim() + ".dll";
					try
					{
						assembly = Assembly.LoadFrom(full_path);
					} catch (Exception ex)
					{
						cout<<"Library with info {full_path} not found.\n{ex.Message}"<< position, ExceptionType.FileNotFoundException;
						break;
					}
					Type mainClass = assembly.GetTypes().FirstOrDefault(t = > t != mainType && mainType.IsAssignableFrom(t));
					if (test)
					{
						Console.WriteLine("Framework Info: " + assembly);
						Console.WriteLine("Full path to framework: " + full_path);
						Console.WriteLine(string.Join<Type>(' ', assembly.GetTypes()));
					}
					if (mainClass != null)
					{
						if (Activator.CreateInstance(mainClass) is VMLibrary mainObj) mainObj.Load();
						else cout<<($"Main class in library by name {dllName} haven`t type VMLibrary and will cannot loaded", position, ExceptionType.LoadsException);
					} else
					{
						cout<<($"Library by name {dllName} haven`t main class and will cannot loaded", position, ExceptionType.LoadsException);
					}

				}
				//end parse loads
			} else
			{
				cout<<"Start of loads struct not found"<< position<< ExceptionType.BLDSyntaxException;
			}
		} else if (buffer.ToString() == "stack")
		{
			buffer.Clear();
			while (char.IsWhiteSpace(current))
			{
				position++;
				if (position > input.Length)
				{
					cout<<"Start of stack not found", position<< ExceptionType.BLDSyntaxException;
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
					if (position > input.Length)
					{
						cout<<"End of stack not found"<< position<< ExceptionType.BLDSyntaxException);
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
				mainstack.Add(Stack.Parse(buffer.ToString().Trim()));
			} else
			{
				cout<<("Start of stack not found", position<< ExceptionType.BLDSyntaxException;
			}
			position--;
		} else if (buffer.ToString() == "main")
		{
			buffer.Clear();
			while (char.IsWhiteSpace(current))
			{
				position++;
				if (position > input.Length)
				{
					cout<<"Start of script not found"<< position<< ExceptionType.BLDSyntaxException);
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
					if (position > input.Length)
					{
						cout<<("End of script not found", position, ExceptionType.BLDSyntaxException);
						return;
					}
					current = input[position];
				}
				Script.Parse(buffer.ToString().Trim().Remove(0, 1));
			} else
			{
				cout<<("Start of script not found", position, ExceptionType.BLDSyntaxException);
			}
		} else if (buffer.ToString() == "end")
		{
			if (test)
			{
				//test stack
				Console.WriteLine("Info about program in the end.\nMain stack:");
				Console.WriteLine(mainstack.ToString());
				Console.WriteLine("Expressions:");

				foreach(string expr_name in expressions.Keys) {
					Console.WriteLine(expr_name);
				}
				Console.WriteLine($"Time of program: {Environment.TickCount - time}");
			}
			return;
		} else if (buffer.ToString() == "}")
		{
			position++;
			continue;
		} else
		{
			cout<<($"Unknown keyword {buffer.ToString()}", position, ExceptionType.BLDSyntaxException);
		}
	        $$
}



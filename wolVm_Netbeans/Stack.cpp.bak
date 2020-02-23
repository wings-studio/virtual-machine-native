#include <iostream>
#include <string>
#include <stdexcept>
#include <stdbool.h>
#include <string.h>
#include "utilMacr.h"
using namespace std;

typedef enum {
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
} ExceptionType;
void ThrowVMException(string message, int position, ExceptionType type);

#define buf_for_itlwm_keyword 10
class StringBuilder {
public:
	l buff[buf_for_itlwm_keyword];
	// Создать новый массив | create new array
	l buff_n[buf_for_itlwm_keyword];
	I ind;
	StringBuilder() {
		ind = 0;
	}
	v Append(l char_) {
		buff[ind] = char_;
		ind++;
	}
	l * ToString() {
		return buff;
	}
	v Clear() {
		this->ind = 0;
	}
	v Terminate() {
		buff[ind + 1] = '\0';
	}
	l* RemoveFirst() {
		strcpy(buff_n, (char*) (&this->ToString()[1]));
		strcpy(buff, buff_n);
		return buff_n;
	}
	I Len() {
		return strlen(buff);
	}
	l * Trim() {// удаляет пробелы c начала строки и конца строки | delete whitespaces from the begging of string and from the end
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
};
StringBuilder buffer;

class Stack {
	//	public Dictionary<string, wolClass> classes;
	//	public Dictionary<string, wolFunction> functions;
	//	public Dictionary<string, Value> values;

	Stack() {
		//		classes = new Dictionary<string, wolClass>();
		//		functions = new Dictionary<string, wolFunction>();
		//		values = new Dictionary<string, Value>();
	}

	/// <summary>
	/// Parsing code of stack and return parsing stack
	/// </summary>
	/// <param name="stack_code">Code of stack with open bracket '{'</param>
	/// <returns></returns>

	Stack Parse(string stack_code) {
		Stack stack = new Stack();
		int position = 0;
		char current = stack_code[0];
		while (current != ' ') //skip whitespaces
		{
			position++;
			if (position > stack_code.size())
			{
				return stack;
			}
			current = stack_code[position];
		}
		if (current == '{')
		{
			try //skip open bracket '{'
			{
				current = stack_code[++position];
			} catch (exception& ex)
			{
				ThrowVMException("End of block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
				return stack;
			}
			StringBuilder buffer = new StringBuilder();
start:
			while (current != '}')
			{
				while (current != ' ') //skip whitespaces
				{
					try
					{
						current = stack_code[++position];
					} catch (exception& ex)
					{
						ThrowVMException("End of block of stack not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
					}
				}
				while (current != '') //get keyword
				{
					try
					{
						buffer.Append(current);
						current = stack_code[++position];
					} catch (exception& ex)
					{
						return stack;
						//ThrowVMException("End of block of stack not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
					}
				}
				if (buffer.ToString() == "class")
				{
					buffer.Clear();
					while (current != ' ') //skip whitespaces
					{
						try
						{
							current = stack_code[++position];
						} catch (exception& ex)
						{
							ThrowVMException("Class haven`t block", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
						}
					}
					if (current == '{')
					{
						while (current != '}')
						{
							if (current != ' ' || current == '{')
								current = stack_code[++position];
							while (current != ' ') //skip whitespaces
							{
								try
								{
									current = stack_code[++position];
								} catch (exception& ex)
								{
									ThrowVMException("Classes`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
								}
							}
							while (current != '') //get name of class
							{
								try
								{
									buffer.Append(current);
									current = stack_code[++position];
								} catch (exception& ex)
								{
									ThrowVMException("Classes`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
								}
							}
							string className = buffer.ToString();
							while (current != ' ') //skip whitespaces
							{
								try
								{
									current = stack_code[++position];
								} catch (exception& ex)
								{
									ThrowVMException("Classes`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);

								}
							}
							buffer.Clear();
							if ((current == '=') || (current == ':'))
							{
								while (current != ' ')
								{
									try
									{
										current = stack_code[++position];
									} catch (exception& ex)
									{
										ThrowVMException("Body of class not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
									}
								}
								while (current != '') //get '='
								{
									try
									{
										buffer.Append(current);
										current = stack_code[++position];
									} catch (exception& ex)
									{
										ThrowVMException("Classes`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);

									}
								}
								while (current != ' ')
								{
									try
									{
										current = stack_code[++position];
									} catch (exception& ex)
									{
										ThrowVMException("Body of class not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
									}
								}
								buffer.Clear();
								while (current != '') //get class type
								{
									try
									{
										buffer.Append(current);
										current = stack_code[++position];
									} catch (exception& ex)
									{
										ThrowVMException("Classes`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);

									}
								}
								wolClass newWolClass = new wolClass(className, SecurityModifer.PUBLIC, wolClassType.DEFAULT, "init"); //create class
								try
								{
									newWolClass.classType = (wolClassType) Enum.Parse(typeof(wolClassType), buffer.ToString(), true); //give type to our class from buffer without case sensetive
								} catch (Exception)
								{
									ThrowVMException($"{buffer.ToString()} is not class type", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
								}
								while (current != ' ')
								{
									try
									{
										current = stack_code[++position];
									} catch (exception& ex)
									{
										ThrowVMException("End of class not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
									}
								}
								buffer.Clear();
								while (current != '') //get security type
								{
									try
									{
										buffer.Append(current);
										current = stack_code[++position];
									} catch (exception& ex)
									{
										ThrowVMException("Classes`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
									}
								}
								try
								{
									newWolClass.security = (SecurityModifer) Enum.Parse(typeof(SecurityModifer), buffer.ToString(), true);
								} catch (Exception)
								{
									ThrowVMException($"{buffer.ToString()} is not security modifer", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
								}
								while (current != ' ')
								{
									try
									{
										current = stack_code[++position];
									} catch (exception& ex)
									{
										ThrowVMException("End of class not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
									}
								}
								if (current == '(')
								{
									buffer.Clear();
									while (current != ')') //get parents
									{
										try
										{
											buffer.Append(current);
											current = stack_code[++position];
										} catch (exception& ex)
										{
											ThrowVMException("Classes`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
										}
									}

									foreach(string parent_name in buffer.ToString().Remove(0, 1).Split(',')) {
										try
										{
											newWolClass.parents.Add(parent_name, VirtualMachine.GetWolClass(parent_name)); //add values in parens to parents of our class
										} catch (Exception)
										{
											//roflanochka
										}
									}
								}
								current = stack_code[++position]; //skip ')'
								while (current == ' ')
								{
									try
									{
										current = stack_code[++position];
									} catch (exception& ex)
									{
										ThrowVMException("End of class not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
									}
								}
								if ((current == ':') || (current == '>')) //check start of class
								{
									while (true) //parse class body
									{
										current = stack_code[++position]; //skip start of class (':' or '>')
										while (current != ' ') //skip whitespaces
										{
											try
											{
												current = stack_code[++position];
											} catch (exception& ex)
											{
												ThrowVMException("Classes`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
											}
										}
										buffer.Clear();
										while (current != '') //get class keyword
										{
											try
											{
												buffer.Append(current);
												if (current > position)
													throw runtime_error("");
												current = stack_code[++position];

											} catch (exception& ex)
											{
												ThrowVMException("Classes`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
											}
										}
										switch (buffer.ToString()) {
										case "constructor":
											buffer.Clear();
											if ((newWolClass.classType == wolClassType.DEFAULT) || newWolClass.classType == wolClassType.STRUCT)
											{
												current = stack_code[++position];
												if (current != '[') //check open bracket
												{
													ThrowVMException("Start of constructors not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
												} else
												{
													while (current != ']')
													{
constructor:
														current = stack_code[++position]; //skip open bracket
														while (current != ' ') //skip whitespaces
														{
															try
															{
																current = stack_code[++position];
															} catch (exception& ex)
															{
																ThrowVMException("Constructor`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
															}
														}
														while (current != '') //get constructor name
														{
															try
															{
																buffer.Append(current);
																current = stack_code[++position];
															} catch (exception& ex)
															{
																ThrowVMException("Constructor`s name not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
															}
														}
														string constrnanme = buffer.ToString();
														buffer.Clear();
														while (current != ' ') //skip whitespaces
														{
															try
															{
																current = stack_code[++position];
															} catch (exception& ex)
															{
																ThrowVMException("Constructor`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
															}
														}
														if (current != '=') //check assignment operator
														{
															ThrowVMException($"Assigment operator isn`t right in constructor {current}", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
														} else
														{
															wolFunction constr = wolFunction.NewDefaultConstructor(newWolClass); //create empty constructor template
															position += 2; //skip whitespace
															current = stack_code[position];
															while (current != '') //get security modifer
															{
																try
																{
																	buffer.Append(current);
																	current = stack_code[++position];
																} catch (exception& ex)
																{
																	ThrowVMException("Constructor`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																}
															}
															constr.security = (SecurityModifer) Enum.Parse(typeof(SecurityModifer), buffer.ToString(), true); //write this modifer to our function
															current = stack_code[++position]; //skip whitespace
															if (current == ':')
															{
																//start parse block
															} else if (current == '(')
															{
																//start parse constructor arguments
																buffer.Clear();
																current = stack_code[++position];
																while (current != ')')
																{
																	buffer.Append(current);
																	try
																	{
																		current = stack_code[++position];
																	} catch (exception& ex)
																	{
																		ThrowVMException("End of arguments not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																	}
																}
																string[] arguments = buffer.ToString().Split(',');

																foreach(string argument in arguments) {
																	string name = argument.Split(':')[0].Trim();
																	wolClass type = VirtualMachine.GetWolClass(argument.Split(':')[1].Trim());
																	constr.arguments.Add(name, type); //add argumrnt (null pointer) to constructor
																}
																//start parse block
															} else
															{
																ThrowVMException("Arguments or start of constructor not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
															}
															current = stack_code[++position];
															//parse block
															while (current != ' ') //skip whitespaces
															{
																try
																{
																	current = stack_code[++position];
																} catch (exception& ex)
																{
																	ThrowVMException("Start of constructor block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																}
															}
															if (current == '[')
															{
																buffer.Clear();
																current = stack_code[++position];
																while (current != ']')
																{
																	try
																	{
																		buffer.Append(current);
																		current = stack_code[++position];
																	} catch (exception& ex)
																	{
																		ThrowVMException("End of block of constructor not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																	}
																}
																constr.body = buffer.ToString();
																buffer.Clear();
																newWolClass.constructors.Add(constrnanme, constr);
																if (stack_code[++position] == ',') goto constructor;
															} else
															{
																ThrowVMException("Start of block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
															}
														}
													}
												}
											} else
											{
												ThrowVMException($"{newWolClass.classType.ToString().ToLower()} don`t support constructors", VirtualMachine.position - stack_code.size() + position, ExceptionType.TypeNotSupportedException);
											}
											break;
										case "func":
											buffer.Clear();
											if (newWolClass.classType == wolClassType.ENUM)
											{
												ThrowVMException("Enum don`t support methods", VirtualMachine.position - stack_code.size() + position, ExceptionType.TypeNotSupportedException);
											} else
											{
												while (current != ' ') //skip whitespaces
												{
													try
													{
														current = stack_code[++position];
													} catch (exception& ex)
													{
														ThrowVMException("Start of methods not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
													}
												}
												if (current != '[') //check open bracket
												{
													ThrowVMException("Start of methods not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
												} else
												{
													current = stack_code[++position]; //skip open bracket '['
function:
													while (current != ']')
													{
														while (current != ' ') //skip whitespaces
														{
															try
															{
																current = stack_code[++position];
															} catch (exception& ex)
															{
																ThrowVMException("Method`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
															}
														}
														while (current != '') //get method name
														{
															try
															{
																buffer.Append(current);
																current = stack_code[++position];
															} catch (exception& ex)
															{
																ThrowVMException("Method`s name not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
															}
														}
														string func_name = buffer.ToString();
														buffer.Clear();
														current = stack_code[++position];
														if (current != '=') //check assignment operator
														{
															ThrowVMException($"Assigment operator isn`t right ('{current}') in method", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
														} else
														{
															wolFunction func = new wolFunction(); //create empty function
															position += 2; //skip whitespace
															current = stack_code[position];
															while (current != '') //get security modifer
															{
																try
																{
																	buffer.Append(current);
																	current = stack_code[++position];
																} catch (exception& ex)
																{
																	ThrowVMException("Method`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																}
															}
															try
															{
																func.security = (SecurityModifer) Enum.Parse(typeof(SecurityModifer), buffer.ToString(), true); //write this modifer to our function
															} catch (ArgumentException)
															{
																ThrowVMException($"{buffer.ToString()} is not secutiry modifer", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
															}
															current = stack_code[++position]; //skip whitespace
															buffer.Clear();
															while (current != '') //get return type
															{
																try
																{
																	buffer.Append(current);
																	current = stack_code[++position];
																} catch (exception& ex)
																{
																	ThrowVMException("Method`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																}
															}
															try
															{
																func.returnType = VirtualMachine.GetWolClass(buffer.ToString());
															} catch (NullReferenceException)
															{
																//ThrowVMException("")
																//don`t need now throw vm exception becouse in GetWolClass was throw exception
															}
															while (current != ' ') //skip whitespaces
															{
																try
																{
																	current = stack_code[++position];
																} catch (exception& ex)
																{
																	ThrowVMException("Start of arguments or method not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																}
															}
															if (current == ':')
															{
																//goto parse_block;
															} else if (current == '(')
															{
																//start parse function arguments
																buffer.Clear();
																current = stack_code[++position]; //skip open paren '('
																while (current != ')')
																{
																	try
																	{
																		buffer.Append(current);
																		current = stack_code[++position];
																	} catch (exception& ex)
																	{
																		ThrowVMException("End of arguments not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																	}
																}
																string[] arguments = buffer.ToString().Split(',');
																foreach(string argument in arguments)
																func.arguments.Add(argument.Split(':')[0].Trim(), VirtualMachine.GetWolClass(argument.Split(':')[1])); //add argumrnt to method
																//current = stack_code[++position]; //skip ')'
															} else
															{
																ThrowVMException($"Arguments or start of method not found ('{current}')", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
															}
															current = stack_code[++position];
															while (current != ' ') //skip whitespaces
															{
																try
																{
																	current = stack_code[++position];
																} catch (exception& ex)
																{
																	ThrowVMException("Start of method block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																}
															}
															if (current == '[')
															{
																buffer.Clear();
																current = stack_code[++position];
																while (current != ']')
																{
																	try
																	{
																		buffer.Append(current);
																		current = stack_code[++position];
																	} catch (exception& ex)
																	{
																		ThrowVMException("End of block of method not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																	}
																}
																func.body = buffer.ToString().Trim();
																newWolClass.methods.Add(func_name, func);
															} else
															{
																ThrowVMException("Start of block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
															}
														}
													}
													if (stack_code[++position] == ',')
													{
														current = stack_code[++position];
														goto function;
													}
												}
											}
											break;
										case "var":
											buffer.Clear();
											if (newWolClass.classType == wolClassType.ENUM)
											{
												ThrowVMException("Enum don`t support variables", VirtualMachine.position - stack_code.size() + position, ExceptionType.TypeNotSupportedException);
											} else
											{
												current = stack_code[++position]; //skip whitespace
												if (current == '[')
												{
													while (current != ']')
													{
variable:
														current = stack_code[++position]; //skip '[' or other character
														while (current != ' ') //skip whitespaces
														{
															try
															{
																current = stack_code[++position];
															} catch (exception& ex)
															{
																ThrowVMException("Variable`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
															}
														}
														while (current != '') //get variable name
														{
															try
															{
																buffer.Append(current);
																current = stack_code[++position];
															} catch (exception& ex)
															{
																ThrowVMException("Variable`s name not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
															}
														}
														string var_name = buffer.ToString();
														buffer.Clear();
														current = stack_code[++position];
														if (current != '=') //check assignment operator
														{
															ThrowVMException($"Assigment operator isn`t right in field ('{current}')", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
														} else
														{

															Value thisVar = Value.VoidValue; //create empty value with parent 'void'
															position += 2; //skip whitespace
															current = stack_code[position];
															while (current != '') //get type
															{
																try
																{
																	buffer.Append(current);
																	current = stack_code[++position];
																} catch (exception& ex)
																{
																	ThrowVMException("Field`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																}
															}
															try
															{
																thisVar.type = VirtualMachine.GetWolClass(buffer.ToString());
															} catch (NullReferenceException)
															{
																//don`t need now throw vm exception becouse in GetWolClass was throw exception
															}
															buffer.Clear();
															current = stack_code[++position]; //skip whitespace
															while (current != '') //get security modifer
															{
																try
																{
																	buffer.Append(current);
																	current = stack_code[++position];
																} catch (exception& ex)
																{
																	ThrowVMException("Field`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																}
															}
															SecurityModifer security = SecurityModifer.PRIVATE;
															try
															{
																security = (SecurityModifer) Enum.Parse(typeof(SecurityModifer), buffer.ToString(), true); //write this modifer to our variable
															} catch (ArgumentException)
															{
																ThrowVMException($"{buffer.ToString()} is not security modifer of setter (getter)", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
															}
															current = stack_code[++position]; //skip whitespace
															buffer.Clear();
															while (current != '') //get name - 'set' or 'get'
															{
																try
																{
																	buffer.Append(current);
																	current = stack_code[++position];
																} catch (exception& ex)
																{
																	ThrowVMException("Field`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																}
															}
															if (buffer.ToString() == "set")
															{
																thisVar.setter.security = security;
																current = stack_code[++position]; //skip whitespace
																if (current == '(')
																{
																	//start parse setter arguments
																	buffer.Clear();
																	current = stack_code[++position];
																	while (current != ')')
																	{
																		buffer.Append(current);
																		try
																		{
																			current = stack_code[++position];
																		} catch (exception& ex)
																		{
																			ThrowVMException("End of arguments not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																		}
																	}
																	string argument = buffer.ToString();
																	string name = argument.Split(':')[0].Trim();
																	wolClass type = VirtualMachine.GetWolClass(argument.Split(':')[1].Trim());
																	thisVar.setter.arguments.Add(name, type); //add argumrnt (null pointer) to setter
																	//start parse block
																} else if (current == ':')
																{
																	//start parse block
																} else
																{
																	ThrowVMException("Arguments or start of setter not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																}
																current = stack_code[++position];
																//parse block
																while (current != ' ') //skip whitespaces
																{
																	try
																	{
																		current = stack_code[++position];
																	} catch (exception& ex)
																	{
																		ThrowVMException("Start of setter block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																	}
																}
																if (current == '[')
																{
																	buffer.Clear();
																	current = stack_code[++position];
																	while (current != ']')
																	{
																		try
																		{
																			buffer.Append(current);
																			current = stack_code[++position];
																		} catch (exception& ex)
																		{
																			ThrowVMException("End of block of fields not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																		}
																	}
																	thisVar.setter.body = buffer.ToString();
																} else
																{
																	ThrowVMException("Start of block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																}
																current = stack_code[++position]; //skip ']'
																while (current != ' ')
																{
																	try
																	{
																		current = stack_code[++position];
																	} catch (exception& ex)
																	{
																		ThrowVMException("Getter security not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																	}
																}
																buffer.Clear();
																while (current != '')
																{
																	try
																	{
																		buffer.Append(current);
																		current = stack_code[++position];
																	} catch (exception& ex)
																	{
																		ThrowVMException("Getter security not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																	}
																}
																try
																{
																	thisVar.getter.security = (SecurityModifer) Enum.Parse(typeof(SecurityModifer), buffer.ToString());
																} catch (ArgumentException)
																{
																	ThrowVMException($"{buffer.ToString()} is not security modifer", VirtualMachine.position - stack_code.size() + position, ExceptionType.NotFoundException);
																}
																while (current != ' ')
																{
																	try
																	{
																		current = stack_code[++position];
																	} catch (exception& ex)
																	{
																		ThrowVMException("Getter not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																	}
																}
																buffer.Clear();
																while (current != '')
																{
																	try
																	{
																		buffer.Append(current);
																		current = stack_code[++position];
																	} catch (exception& ex)
																	{
																		ThrowVMException("Getter not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																	}
																}
																if (buffer.ToString() != "get")
																{
																	ThrowVMException($"Unknown keyword {buffer.ToString()}", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																}
															} else if (buffer.ToString() != "get")
															{
																ThrowVMException($"Unknown keyword {buffer.ToString()}", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
															}
															current = stack_code[++position];
															//parse block
															while (current != ' ') //skip whitespaces
															{
																try
																{
																	current = stack_code[++position];
																} catch (exception& ex)
																{
																	ThrowVMException("Start of getter block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																}
															}
															if (current == '[')
															{
																buffer.Clear();
																current = stack_code[++position];
																while (current != ']')
																{
																	try
																	{
																		buffer.Append(current);
																		current = stack_code[++position];
																	} catch (exception& ex)
																	{
																		ThrowVMException("End of block of fields not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																	}
																}
																thisVar.getter.body = buffer.ToString();
																buffer.Clear();
																newWolClass.fields.Add(var_name, thisVar);
																if (stack_code[++position] == ',') goto variable;
															} else
															{
																ThrowVMException("Start of block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
															}
														}
													}
												} else
												{
													ThrowVMException("Start of fields not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
												}
											}
											break;
										case "const":
											if ((newWolClass.classType == wolClassType.ENUM) || (newWolClass.classType == wolClassType.STRUCT))
											{
												while (current != ' ') //skip whitespaces
												{
													try
													{
														current = stack_code[++position];
													} catch (exception& ex)
													{
														ThrowVMException("Start of constants not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
													}
												}
												if (current == '[')
												{
													while (current != ']')
													{
														try
														{
															current = stack_code[++position];
														} catch (exception& ex)
														{
															ThrowVMException("End of constants block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
														} //it`s time solution
													}
												} else
												{
													ThrowVMException("Open brackets in constants not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
												}
											} else
											{
												ThrowVMException($"{newWolClass.classType.ToString().ToLower()} don`t support constants", VirtualMachine.position - stack_code.size() + position, ExceptionType.TypeNotSupportedException);
											}
											break;
										case "],": //костыль(
											continue;
										case "];":
										case ";": //тоже костыли но без них никак :)
											buffer.Clear();
											goto out_cycle;
										default:
											ThrowVMException($"Unknown keyword {buffer.ToString()} in the class initilization", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
											break;
										}
									}
out_cycle:
									try
									{
										stack.classes.Add(className, newWolClass); //add to return stack this class
									} catch (ArgumentException)
									{
										//pass
									}
								} else
								{
									ThrowVMException("Start of block operator is not valid", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
								}
							} else
							{
								ThrowVMException($"Assigment operator in class initilization is not valid ('{current}')", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
							}
							while (current != ' ')
							{
								try
								{
									current = stack_code[++position];
								} catch (exception& ex)
								{
									ThrowVMException("End of classes not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
								}
							}
						}
					} else
					{
						ThrowVMException("Classes`s start not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
					}
					buffer.Clear();
				} else if (buffer.ToString() == "func")
				{
					buffer.Clear();
					while (current != ' ') //skip whitespaces
					{
						try
						{
							current = stack_code[++position];
						} catch (exception& ex)
						{
							ThrowVMException("Functions is empty", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
						}
					}
					if (current == '{')
					{
						while (current != '}')
						{
function:
							current = stack_code[++position]; //skip '{'
							while (current != ' ') //skip whitespaces
							{
								try
								{
									current = stack_code[++position];
								} catch (exception& ex)
								{
									ThrowVMException("Function`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
								}
							}
							while (current != '') //get function name
							{
								try
								{
									buffer.Append(current);
									current = stack_code[++position];
								} catch (exception& ex)
								{
									ThrowVMException("Function`s name not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
								}
							}
							string func_name = buffer.ToString();
							buffer.Clear();
							current = stack_code[++position];
							if (current != '=') //check assignment operator
							{
								ThrowVMException($"Assigment operator isn`t right in fucntion ('{current}')", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
							} else
							{

								wolFunction func = new wolFunction(); //create empty function
								position += 2; //skip whitespace
								current = stack_code[position];
								while (current != '') //get security modifer
								{
									try
									{
										buffer.Append(current);
										current = stack_code[++position];
									} catch (exception& ex)
									{
										ThrowVMException("Function`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
									}
								}
								func.security = (SecurityModifer) Enum.Parse(typeof(SecurityModifer), buffer.ToString(), true); //write this modifer to our function
								current = stack_code[++position]; //skip whitespace
								buffer.Clear();
								while (current != '') //get return type
								{
									try
									{
										buffer.Append(current);
										current = stack_code[++position];
									} catch (exception& ex)
									{
										ThrowVMException("Function`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
									}
								}
								try
								{
									func.returnType = VirtualMachine.GetWolClass(buffer.ToString());
								} catch (NullReferenceException)
								{
									//don`t need now throw vm exception becouse in GetWolClass was throw exception
								}
								current = stack_code[++position]; //skip whitespace
								if (current == ':')
								{
									//start parse block
								} else if (current == '(')
								{
									//start parse function arguments
									buffer.Clear();
									current = stack_code[++position];
									while (current != ')')
									{
										buffer.Append(current);
										try
										{
											current = stack_code[++position];
										} catch (exception& ex)
										{
											ThrowVMException("End of arguments not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
										}
									}
									string[] arguments = buffer.ToString().Split(',');

									foreach(string argument in arguments) {
										string name = argument.Split(':')[0].Trim();
										wolClass type = VirtualMachine.GetWolClass(argument.Split(':')[1].Trim());
										func.arguments.Add(name, type); //add argumrnt (null pointer) to function
									}
									//start parse block
								} else
								{
									ThrowVMException($"Arguments or start of function not found ('{current}')", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
								}
								current = stack_code[++position];
								//parse block
								while (current != ' ') //skip whitespaces
								{
									try
									{
										current = stack_code[++position];
									} catch (exception& ex)
									{
										ThrowVMException("Start of function block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
									}
								}
								if (current == '[')
								{
									buffer.Clear();
									current = stack_code[++position];
									while (current != ']')
									{
										try
										{
											buffer.Append(current);
											current = stack_code[++position];
										} catch (exception& ex)
										{
											ThrowVMException("End of block of function not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
										}
									}
									func.body = buffer.ToString();
									stack.functions.Add(func_name, func);
									current = stack_code[++position]; //skip ']' (peek next char)
									buffer.Clear();
									if (current == ',')
									{
										current = stack_code[++position]; //skip ','
										goto function;
									}
									while (current != ' ')
									{
										try
										{
											current = stack_code[++position];
										} catch (exception& ex)
										{
											ThrowVMException("End of functions not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
										}
									}
								} else
								{
									ThrowVMException("Start of block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
								}
							}
						}
					} else
					{
						ThrowVMException("Functions`s start not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
					}
				} else if (buffer.ToString() == "var")
				{
					buffer.Clear();
					while (current != ' ') //skip whitespaces
					{
						try
						{
							current = stack_code[++position];
						} catch (exception& ex)
						{
							ThrowVMException("Variables is empty", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
						}
					}
					if (current == '{')
					{
						while (current != '}')
						{
variable:
							current = stack_code[++position]; //skip '{'
							while (current != ' ') //skip whitespaces
							{
								try
								{
									current = stack_code[++position];
								} catch (exception& ex)
								{
									ThrowVMException("Variable`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
								}
							}
							while (current != '') //get variable name
							{
								try
								{
									buffer.Append(current);
									current = stack_code[++position];
								} catch (exception& ex)
								{
									ThrowVMException("Variable`s name not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
								}
							}
							string var_name = buffer.ToString();
							buffer.Clear();
							current = stack_code[++position];
							if (current != '=') //check assignment operator
							{
								ThrowVMException("Assigment operator isn`t right in variable", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
							} else
							{

								Value thisVar = Value.VoidValue; //create empty value with parent 'void'
								position += 2;
								current = stack_code[position]; //skip whitespace
								buffer.Clear();
								while (current != '') //get type
								{
									try
									{
										buffer.Append(current);
										current = stack_code[++position];
									} catch (exception& ex)
									{
										ThrowVMException("Variable`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
									}
								}
								try
								{
									thisVar.type = VirtualMachine.GetWolClass(buffer.ToString());
								} catch (NullReferenceException)
								{
									//ThrowVMException("")
									//don`t need now throw vm exception becouse in GetWolClass was throw exception
								}
								buffer.Clear();
								current = stack_code[++position];
								while (current != '') //get security modifer
								{
									try
									{
										buffer.Append(current);
										current = stack_code[++position];
									} catch (exception& ex)
									{
										ThrowVMException("Variable`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
									}
								}
								SecurityModifer security = SecurityModifer.PRIVATE;
								try
								{
									security = (SecurityModifer) Enum.Parse(typeof(SecurityModifer), buffer.ToString(), true); //write this modifer to our variable
								} catch (Exception)
								{
									ThrowVMException($"{buffer.ToString()} is not security modifer", VirtualMachine.position - stack_code.size() + position, ExceptionType.NotFoundException);
								}
								current = stack_code[++position]; //skip whitespace
								buffer.Clear();
								while (current != '') //get name - 'set' or 'get'
								{
									try
									{
										buffer.Append(current);
										current = stack_code[++position];
									} catch (exception& ex)
									{
										ThrowVMException("Variable`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
									}
								}
								if (buffer.ToString() == "set")
								{
									thisVar.setter.security = security;
									current = stack_code[++position];
									if (current == '(')
									{
										//start parse setter arguments
										buffer.Clear();
										current = stack_code[++position];
										while (current != ')')
										{
											buffer.Append(current);
											try
											{
												current = stack_code[++position];
											} catch (exception& ex)
											{
												ThrowVMException("End of arguments not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
											}
										}
										string argument = buffer.ToString();
										string name = argument.Split(':')[0].Trim();
										wolClass type = VirtualMachine.GetWolClass(argument.Split(':')[1].Trim());
										thisVar.setter.arguments.Add(name, type); //add argumrnt (null pointer) to setter
										//start parse block
									} else if (current == ':')
									{
										//start parse block
									} else
									{
										ThrowVMException("Arguments or start of setter not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
									}
									current = stack_code[++position];
									//parse block
									while (current != ' ') //skip whitespaces
									{
										try
										{
											current = stack_code[++position];
										} catch (exception& ex)
										{
											ThrowVMException("Start of setter block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
										}
									}
									if (current == '[')
									{
										buffer.Clear();
										current = stack_code[++position];
										while (current != ']')
										{
											try
											{
												buffer.Append(current);
												current = stack_code[++position];
											} catch (exception& ex)
											{
												ThrowVMException("End of block of variables not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
											}
										}
										thisVar.setter.body = buffer.ToString();
									} else
									{
										ThrowVMException("Start of setter block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
									}
									current = stack_code[++position]; //skip ']'
									while (current != ' ')
									{
										try
										{
											current = stack_code[++position];
										} catch (exception& ex)
										{
											ThrowVMException("Getter security not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
										}
									}
									buffer.Clear();
									while (current != '')
									{
										try
										{
											buffer.Append(current);
											current = stack_code[++position];
										} catch (exception& ex)
										{
											ThrowVMException("Getter security not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
										}
									}
									try
									{
										thisVar.getter.security = (SecurityModifer) Enum.Parse(typeof(SecurityModifer), buffer.ToString());
									} catch (ArgumentException)
									{
										ThrowVMException($"{buffer.ToString()} is not security modifer", VirtualMachine.position - stack_code.size() + position, ExceptionType.NotFoundException);
									}
									while (current != ' ')
									{
										try
										{
											current = stack_code[++position];
										} catch (exception& ex)
										{
											ThrowVMException("Getter not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
										}
									}
									buffer.Clear();
									while (current != '')
									{
										try
										{
											buffer.Append(current);
											current = stack_code[++position];
										} catch (exception& ex)
										{
											ThrowVMException("Getter not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
										}
									}
									if (buffer.ToString() != "get")
									{
										ThrowVMException($"Unknown keyword {buffer.ToString()}", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
									}
								} else if (buffer.ToString() != "get")
								{
									ThrowVMException($"Unknown keyword {buffer.ToString()}", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
								}
								current = stack_code[++position];
								//parse block
								while (current != ' ') //skip whitespaces
								{
									try
									{
										current = stack_code[++position];
									} catch (exception& ex)
									{
										ThrowVMException("Start of getter block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
									}
								}
								if (current == '[')
								{
									buffer.Clear();
									current = stack_code[++position];
									while (current != ']')
									{
										try
										{
											buffer.Append(current);
											current = stack_code[++position];
										} catch (exception& ex)
										{
											ThrowVMException("End of block of variables not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
										}
									}
									thisVar.getter.body = buffer.ToString();
								} else
								{
									ThrowVMException("Start of getter block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
								}
								//Console.WriteLine("Var name: " + var_name);
								//Console.WriteLine("Setter: " + thisVar.setter.body);
								stack.values.Add(var_name, thisVar);
								current = stack_code[++position]; //skip ']'
								if (current == ',')
								{
									current = stack_code[++position];
									goto variable;
								}
								while (current != ' ')
								{
									try
									{
										current = stack_code[++position];
									} catch (exception& ex)
									{
										ThrowVMException("End of functions not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
									}
								}
							}
						}
					} else
					{
						ThrowVMException("Variables`s start not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
					}
					buffer.Clear();
				} else
				{
					ThrowVMException($"Unknown keyword {buffer.ToString()} in stack initilization", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
				}
				try
				{
					if (stack_code[++position] == ';')
					{
						current = stack_code[++position]; //skip semicolon
						goto start;
					}
				} catch (exception& ex)
				{
					return stack;
				}
			}
			//Console.WriteLine($"Classes length {stack.classes.Count}  funс {stack.functions.Count} vars {stack.values.Count}"); //test
			return stack;
		} else
		{
			ThrowVMException("Start of block is not '{'", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
			return stack;
		}
	}

	public

	void Add(Stack stack) {
		if (stack.classes.Count != 0)
		{

			foreach(KeyValuePair<string, wolClass> cl in stack.classes) {
				classes.Add(cl.Key, cl.Value);
			}
		}
		if (stack.functions.Count != 0)
		{

			foreach(KeyValuePair<string, wolFunction> fn in stack.functions) {
				functions.Add(fn.Key, fn.Value);
			}
		}
		if (stack.values.Count != 0)
		{

			foreach(KeyValuePair<string, Value> vl in stack.values) {
				values.Add(vl.Key, vl.Value);
			}
		}
	}

	public

	void Remove(Value[] elems) {
		//pass
	}

	public

	void Dispose() {
		classes.Clear();
		functions.Clear();
		values.Clear();
	}

	public

	override string ToString() {
		string str = "";

		foreach(KeyValuePair<string, Value> keyValuePair in values) {
			str += keyValuePair.Key + ' ' + keyValuePair.Value + '\n';
		}

		foreach(KeyValuePair<string, wolClass> keyValuePair in classes) {
			str += keyValuePair.Key + ' ' + keyValuePair.Value + '\n';
		}

		foreach(KeyValuePair<string, wolFunction> keyValuePair in functions) {
			str += keyValuePair.Key + ' ' + keyValuePair.Value + '\n';
		}
		return str;
	}

	public

	static Stack operator +(Stack right, Stack left) {
		Stack ret = new Stack();
		ret.Add(right);
		ret.Add(left);
		return ret;
	}

	public

	static Stack operator +(Stack right, Dictionary<string, Value> left) {
		foreach(KeyValuePair<string, Value> vari in left)
		right.values.Add(vari.Key, vari.Value);
		return right;
	}

	public

	static Stack operator +(Stack right, Dictionary<string, wolClass> left) {
		foreach(KeyValuePair<string, wolClass> vari in left)
		right.classes.Add(vari.Key, vari.Value);
		return right;
	}

	public

	static Stack operator +(Stack right, Dictionary<string, wolFunction> left) {
		foreach(KeyValuePair<string, wolFunction> vari in left)
		right.functions.Add(vari.Key, vari.Value);
		return right;
	}

	public

	static Stack operator -(Stack right, Dictionary<string, Value> left) {

		foreach(string arg in left.Keys) {
			right.values.Remove(arg);
		}
		return right;
	}
}

void ThrowVMException(string message, int position, ExceptionType type) {
	cout << type << "Exception in position{" << position << "}" << message << endl;
}



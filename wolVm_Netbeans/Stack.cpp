#include <iostream>
#include <string>
#include <stdexcept>
#include <stdbool.h>
#include <string.h>
#include <map>
#include "utilMacr.h"
#include "Enums.h"
#include "SB.h"
#include "Value.h"
#include "wolFunction.h"
#include "wolClass.h"
#include "VirtualMachine.h"
using namespace std;
extern StringBuilder buffer;
extern Stack stack;
extern wolClass wolClass_o;
extern wolFunction wolFunction_o;
extern Value value;
extern VirtualMachine VirtualMachine;
Stack::Stack() {
	map<string, wolClass> classes();
	map<string, wolFunction> functions();
	map<string, Value> values();
}
/// <summary>
/// Parsing code of stack and return parsing stack
/// </summary>
/// <param name="stack_code">Code of stack with open bracket '{'</param>
/// <returns></returns>
void Stack::Add(Stack stack) {
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
void Stack::Remove(Value[] elems) {
	//pass
}
void Stack::Dispose() {
	classes.Clear();
	functions.Clear();
	values.Clear();
}
string Stack::ToString() {
	string str = "";
	foreach(KeyValuePair<string, Value> keyValuePair in values) {
		str += keyValuePair.Key + ' ' + keyValuePair.Value + '';
	}
	foreach(KeyValuePair<string, wolClass> keyValuePair in classes) {
		str += keyValuePair.Key + ' ' + keyValuePair.Value + '';
	}
	foreach(KeyValuePair<string, wolFunction> keyValuePair in functions) {
		str += keyValuePair.Key + ' ' + keyValuePair.Value + '';
	}
	return str;
}
Stack operator +(Stack right, Stack left) {
	Stack ret = new Stack();
	ret.Add(right);
	ret.Add(left);
	return ret;
}
Stack Stack::operator +(Stack right, map<string, Value> left) {
	foreach(KeyValuePair<string, Value> vari in left)
	right.values.Add(vari.Key, vari.Value);
	return right;
}
Stack Stack::operator +(Stack right, map<string, wolClass> left) {
	foreach(KeyValuePair<string, wolClass> vari in left)
	right.classes.Add(vari.Key, vari.Value);
	return right;
}
Stack Stack::operator +(Stack right, map<string, wolFunction> left) {
	foreach(KeyValuePair<string, wolFunction> vari in left)
	right.functions.Add(vari.Key, vari.Value);
	return right;
}
Stack Stack::Parse(string stack_code) {
	int position = 0;
	char current = stack_code[0];
	while (current != ' ') //skip whitespaces
	{
		position++;
		if (position > stack_code.size())
		{
			return this;
		}
		current = stack_code[position];
	}
	if (current == '{')
	{
		try //skip open bracket '{'
		{
			current = stack_code[++position];
			if (position > stack_code.size()) throw runtime_error("");
		} catch (exception& ex)
		{
			VirtualMachine.ThrowVMException("End of block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
			return this;
		}
start:
		while (current != '}')
		{
			while (current != ' ') //skip whitespaces
			{
				try
				{
					current = stack_code[++position];
					if (position > stack_code.size()) throw runtime_error("");
				} catch (exception& ex)
				{
					VirtualMachine.ThrowVMException("End of block of stack not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
				}
			}
			while (current != ' ') //get keyword
			{
				try
				{
					buffer.Append(current);
					current = stack_code[++position];
					if (position > stack_code.size()) throw runtime_error("");
				} catch (exception& ex)
				{
					return this;
					//VirtualMachine.ThrowVMException("End of block of stack not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
				}
			}
			if (buffer.ToStringCpp().equal("class"))
			{
				buffer.Clear();
				while (current != ' ') //skip whitespaces
				{
					try
					{
						current = stack_code[++position];
						if (position > stack_code.size()) throw runtime_error("");
					} catch (exception& ex)
					{
						VirtualMachine.ThrowVMException("Class haven`t block", /*VirtualMachine.position -*/ stack_code.size() + position, BLDSyntaxException);
					}
				}
				if (current == '{')
				{
					while (current != '}')
					{
						if (current != ' ' || current == '{')
							current = stack_code[++position];
						if (position > stack_code.size()) throw runtime_error("");
						while (current != ' ') //skip whitespaces
						{
							try
							{
								current = stack_code[++position];
								if (position > stack_code.size()) throw runtime_error("");
							} catch (exception& ex)
							{
								VirtualMachine.ThrowVMException("Classes`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
							}
						}
						while (current != ' ') //get name of class
						{
							try
							{
								buffer.Append(current);
								current = stack_code[++position];
								if (position > stack_code.size()) throw runtime_error("");
							} catch (exception& ex)
							{
								VirtualMachine.ThrowVMException("Classes`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
							}
						}
						string className = buffer.ToStringCpp();
						while (current != ' ') //skip whitespaces
						{
							try
							{
								current = stack_code[++position];
								if (position > stack_code.size()) throw runtime_error("");
							} catch (exception& ex)
							{
								VirtualMachine.ThrowVMException("Classes`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
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
									if (position > stack_code.size()) throw runtime_error("");
								} catch (exception& ex)
								{
									VirtualMachine.ThrowVMException("Body of class not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
								}
							}
							while (current != ' ') //get '='
							{
								try
								{
									buffer.Append(current);
									current = stack_code[++position];
									if (position > stack_code.size()) throw runtime_error("");
								} catch (exception& ex)
								{
									VirtualMachine.ThrowVMException("Classes`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
								}
							}
							while (current != ' ')
							{
								try
								{
									current = stack_code[++position];
									if (position > stack_code.size()) throw runtime_error("");
								} catch (exception& ex)
								{
									VirtualMachine.ThrowVMException("Body of class not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
								}
							}
							buffer.Clear();
							while (current != ' ') //get class type
							{
								try
								{
									buffer.Append(current);
									current = stack_code[++position];
									if (position > stack_code.size()) throw runtime_error("");
								} catch (exception& ex)
								{
									VirtualMachine.ThrowVMException("Classes`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
								}
							}
							wolClass newWolClass = new wolClass(className, SecurityModifer.PUBLIC, wolClassType.DEFAULT, "init"); //create class
							try
							{
								newWolClass.classType = (wolClassType) Enum.Parse(typeof(wolClassType), buffer.ToStringCpp()(, true); //give type to our class from buffer without case sensetive
							} catch (exception& ex)
							{
								VirtualMachine.ThrowVMException("{buffer.ToStringCpp().equal(} is not class type", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
							}
							while (current != ' ')
							{
								try
								{
									current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
									} catch (exception& ex)
								{
									VirtualMachine.ThrowVMException("End of class not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
								}
							}
							buffer.Clear();
							while (current != ' ') //get security type
							{
								try
								{
									buffer.Append(current);
										current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
									} catch (exception& ex)
								{
									VirtualMachine.ThrowVMException("Classes`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
								}
							}
							try
							{
								newWolClass.security = (SecurityModifer) Enum.Parse(typeof(SecurityModifer), buffer.ToStringCpp().equal(, true);
							} catch (Exception)
							{
								VirtualMachine.ThrowVMException("{buffer.ToStringCpp().equal(} is not security modifer", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
							}
							while (current != ' ')
							{
								try
								{
									current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
									} catch (exception& ex)
								{
									VirtualMachine.ThrowVMException("End of class not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
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
											current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
										} catch (exception& ex)
									{
										VirtualMachine.ThrowVMException("Classes`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
									}
								}
								foreach(string parent_name in buffer.ToStringCpp().equal(.Remove(0, 1).Split(',')) {
									try
									{
										newWolClass.parents.Add(parent_name, VirtualMachine.GetWolClass(parent_name)); //add values in parens to parents of our class
									} catch (Exception)
									{
										//roflanochka
									}
								}
							}
							current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error(""); //skip ')'
								while (current == ' ')
								{
									try
									{
										current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
										} catch (exception& ex)
									{
										VirtualMachine.ThrowVMException("End of class not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
									}
								}
							if ((current == ':') || (current == '>')) //check start of class
							{
								while (true) //parse class body
								{
									current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error(""); //skip start of class (':' or '>')
										while (current != ' ') //skip whitespaces
										{
											try
											{
												current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
												} catch (exception& ex)
											{
												VirtualMachine.ThrowVMException("Classes`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
											}
										}
									buffer.Clear();
									while (current != ' ') //get class keyword
									{
										try
										{
											buffer.Append(current);
											if (current > position)
												throw runtime_error("");
												current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
												} catch (exception& ex)
										{
											VirtualMachine.ThrowVMException("Classes`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
										}
									}
									switch (buffer.ToStringCpp()) {
									case "constructor":
										buffer.Clear();
										if ((newWolClass.classType == wolClassType.DEFAULT) || newWolClass.classType == wolClassType.STRUCT)
										{
											current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
												if (current != '[') //check open bracket
												{
													VirtualMachine.ThrowVMException("Start of constructors not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
												} else
												{
													while (current != ']')
													{
constructor:
														current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error(""); //skip open bracket
															while (current != ' ') //skip whitespaces
															{
																try
																{
																	current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																	} catch (exception& ex)
																{
																	VirtualMachine.ThrowVMException("Constructor`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																}
															}
														while (current != ' ') //get constructor name
														{
															try
															{
																buffer.Append(current);
																	current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																} catch (exception& ex)
															{
																VirtualMachine.ThrowVMException("Constructor`s name not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
															}
														}
														string constrnanme = buffer.ToStringCpp().equal(;
															buffer.Clear();
														while (current != ' ') //skip whitespaces
														{
															try
															{
																current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																} catch (exception& ex)
															{
																VirtualMachine.ThrowVMException("Constructor`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
															}
														}
														if (current != '=') //check assignment operator
														{
															VirtualMachine.ThrowVMException("Assigment operator isn`t right in constructor {current}", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
														} else
														{
															//															wolFunction constr = wolFunction.NewDefaultConstructor(newWolClass); //create empty constructor template
															position += 2; //skip whitespace
																current = stack_code[position];
															while (current != ' ') //get security modifer
															{
																try
																{
																	buffer.Append(current);
																		current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																	} catch (exception& ex)
																{
																	VirtualMachine.ThrowVMException("Constructor`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																}
															}
															constr.security = (SecurityModifer) Enum.Parse(typeof(SecurityModifer), buffer.ToStringCpp().equal(, true); //write stack modifer to our function
																current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error(""); //skip whitespace
																if (current == ':')
																{
																	//start parse block
																} else if (current == '(')
																{
																	//start parse constructor arguments
																	buffer.Clear();
																		current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																		while (current != ')')
																		{
																			buffer.Append(current);
																			try
																			{
																				current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																				} catch (exception& ex)
																			{
																				VirtualMachine.ThrowVMException("End of arguments not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																			}
																		}
																	string[] arguments = buffer.ToStringCpp().equal(.Split(',');
																		foreach(string argument in arguments) {
																		string name = argument.Split(':')[0].Trim();
																			wolClass type = VirtualMachine.GetWolClass(argument.Split(':')[1].Trim());
																			constr.arguments.Add(name, type); //add argumrnt (null pointer) to constructor
																	}
																	//start parse block
																} else
																{
																	VirtualMachine.ThrowVMException("Arguments or start of constructor not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																}
															current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																//parse block
																while (current != ' ') //skip whitespaces
																{
																	try
																	{
																		current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																		} catch (exception& ex)
																	{
																		VirtualMachine.ThrowVMException("Start of constructor block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																	}
																}
															if (current == '[')
															{
																buffer.Clear();
																	current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																	while (current != ']')
																	{
																		try
																		{
																			buffer.Append(current);
																				current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																			} catch (exception& ex)
																		{
																			VirtualMachine.ThrowVMException("End of block of constructor not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																		}
																	}
																constr.body = buffer.ToStringCpp().equal(;
																	buffer.Clear();
																	newWolClass.constructors.Add(constrnanme, constr);
																if (stack_code[++position] == ',') goto constructor;
																} else
															{
																VirtualMachine.ThrowVMException("Start of block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
															}
														}
													}
												}
										} else
										{
											VirtualMachine.ThrowVMException("{newWolClass.classType.ToString().ToLower()} don`t support constructors", VirtualMachine.position - stack_code.size() + position, ExceptionType.TypeNotSupportedException);
										}
										break;
									case "func":
										buffer.Clear();
										if (newWolClass.classType == wolClassType.ENUM)
										{
											VirtualMachine.ThrowVMException("Enum don`t support methods", VirtualMachine.position - stack_code.size() + position, ExceptionType.TypeNotSupportedException);
										} else
										{
											while (current != ' ') //skip whitespaces
											{
												try
												{
													current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
													} catch (exception& ex)
												{
													VirtualMachine.ThrowVMException("Start of methods not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
												}
											}
											if (current != '[') //check open bracket
											{
												VirtualMachine.ThrowVMException("Start of methods not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
											} else
											{
												current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error(""); //skip open bracket '['
													function :
													while (current != ']')
													{
														while (current != ' ') //skip whitespaces
														{
															try
															{
																current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																} catch (exception& ex)
															{
																VirtualMachine.ThrowVMException("Method`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
															}
														}
														while (current != ' ') //get method name
														{
															try
															{
																buffer.Append(current);
																	current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																} catch (exception& ex)
															{
																VirtualMachine.ThrowVMException("Method`s name not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
															}
														}
														string func_name = buffer.ToStringCpp();
															buffer.Clear();
															current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
															if (current != '=') //check assignment operator
															{
																VirtualMachine.ThrowVMException("Assigment operator isn`t right ('{current}') in method", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
															} else
															{
																//															wolFunction func = new wolFunction(); //create empty function
																position += 2; //skip whitespace
																	current = stack_code[position];
																while (current != ' ') //get security modifer
																{
																	try
																	{
																		buffer.Append(current);
																			current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																		} catch (exception& ex)
																	{
																		VirtualMachine.ThrowVMException("Method`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																	}
																}
																try
																{
																	//																func.security = (SecurityModifer) Enum.Parse(typeof(SecurityModifer), buffer.ToStringCpp().equal(, true); //write stack modifer to our function
																} catch (exception& ex)
																{
																	VirtualMachine.ThrowVMException("{buffer.ToStringCpp()} is not secutiry modifer", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																}
																current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error(""); //skip whitespace
																	buffer.Clear();
																	while (current != ' ') //get return type
																	{
																		try
																		{
																			buffer.Append(current);
																				current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																			} catch (exception& ex)
																		{
																			VirtualMachine.ThrowVMException("Method`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																		}
																	}
																try
																{
																	//																func.returnType = VirtualMachine.GetWolClass(buffer.ToStringCpp();
																} catch (exception& ex)
																{
																	//VirtualMachine.ThrowVMException("")
																	//don`t need now throw vm exception becouse in GetWolClass was throw exception
																}
																while (current != ' ') //skip whitespaces
																{
																	try
																	{
																		current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																		} catch (exception& ex)
																	{
																		VirtualMachine.ThrowVMException("Start of arguments or method not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																	}
																}
																if (current == ':')
																{
																	//goto parse_block;
																} else if (current == '(')
																{
																	//start parse function arguments
																	buffer.Clear();
																		current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error(""); //skip open paren '('
																		while (current != ')')
																		{
																			try
																			{
																				buffer.Append(current);
																					current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																				} catch (exception& ex)
																			{
																				VirtualMachine.ThrowVMException("End of arguments not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																			}
																		}
																	string[] arguments = buffer.ToStringCpp().Split(',');
																		//																foreach(string argument in arguments)
																		//																func.arguments.Add(argument.Split(':')[0].Trim(), VirtualMachine.GetWolClass(argument.Split(':')[1])); //add argumrnt to method
																		//current = stack_code[++position];if(position>stack_code.size()) throw runtime_error(""); //skip ')'
																} else
																{
																	VirtualMachine.ThrowVMException("Arguments or start of method not found ('{current}')", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																}
																current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																	while (current != ' ') //skip whitespaces
																	{
																		try
																		{
																			current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																			} catch (exception& ex)
																		{
																			VirtualMachine.ThrowVMException("Start of method block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																		}
																	}
																if (current == '[')
																{
																	buffer.Clear();
																		current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																		while (current != ']')
																		{
																			try
																			{
																				buffer.Append(current);
																					current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																				} catch (exception& ex)
																			{
																				VirtualMachine.ThrowVMException("End of block of method not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																			}
																		}
																	//																func.body = buffer.ToStringCpp().Trim();
																	//																newWolClass.methods.Add(func_name, func);
																} else
																{
																	VirtualMachine.ThrowVMException("Start of block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																}
															}
													}
												if (stack_code[++position] == ',')
												{
													current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
														goto function;
													}
											}
										}
										break;
									case "var":
										buffer.Clear();
										if (/*newWolClass.classType == wolClassType.ENUM*/)
										{
											VirtualMachine.ThrowVMException("Enum don`t support variables", VirtualMachine.position - stack_code.size() + position, TypeNotSupportedException);
										} else
										{
											current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error(""); //skip whitespace
												if (current == '[')
												{
													while (current != ']')
													{
variable:
														current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error(""); //skip '[' or other character
															while (current != ' ') //skip whitespaces
															{
																try
																{
																	current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																	} catch (exception& ex)
																{
																	VirtualMachine.ThrowVMException("Variable`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																}
															}
														while (current != ' ') //get variable name
														{
															try
															{
																buffer.Append(current);
																	current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																} catch (exception& ex)
															{
																VirtualMachine.ThrowVMException("Variable`s name not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
															}
														}
														string var_name = buffer.ToStringCpp();
															buffer.Clear();
															current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
															if (current != '=') //check assignment operator
															{
																VirtualMachine.ThrowVMException("Assigment operator isn`t right in field ('{current}')", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
															} else
															{
																//															Value stackVar = Value.VoidValue; //create empty value with parent 'void'
																position += 2; //skip whitespace
																	current = stack_code[position];
																while (current != '') //get type
																{
																	try
																	{
																		buffer.Append(current);
																			current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																		} catch (exception& ex)
																	{
																		VirtualMachine.ThrowVMException("Field`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																	}
																}
																try
																{
																	//																stackVar.type = VirtualMachine.GetWolClass(buffer.ToStringCpp();
																} catch (exception& ex)
																{
																	//don`t need now throw vm exception becouse in GetWolClass was throw exception
																}
																buffer.Clear();
																	current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error(""); //skip whitespace
																	//															while (current != ' ') //get security modifer
																	//															{
																	//																try
																	//																{
																	//																	buffer.Append(current);
																	//																	current = stack_code[++position];if(position>stack_code.size()) throw runtime_error("");
																	//																} catch (exception& ex)
																	//																{
																	//																	VirtualMachine.ThrowVMException("Field`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																	//																}
																	//															}
																	//															SecurityModifer security = SecurityModifer.PRIVATE;
																	//															try
																	//															{
																	////																security = (SecurityModifer) Enum.Parse(typeof(SecurityModifer), buffer.ToStringCpp()(, true); //write stack modifer to our variable
																	//															} catch (ArgumentException)
																	//															{
																	//																VirtualMachine.ThrowVMException("{buffer.ToStringCpp()} is not security modifer of setter (getter)", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																	//															}
																	current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error(""); //skip whitespace
																		buffer.Clear();
																		while (current != ' ') //get name - 'set' or 'get'
																		{
																			try
																			{
																				buffer.Append(current);
																					current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																				} catch (exception& ex)
																			{
																				VirtualMachine.ThrowVMException("Field`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																			}
																		}
																if (buffer.ToStringCpp().equal("set"))
																{
																	//																stackVar.setter.security = security;
																	current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error(""); //skip whitespace
																		if (current == '(')
																		{
																			//start parse setter arguments
																			buffer.Clear();
																				current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																				while (current != ')')
																				{
																					buffer.Append(current);
																					try
																					{
																						current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																						} catch (exception& ex)
																					{
																						VirtualMachine.ThrowVMException("End of arguments not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																					}
																				}
																			string argument = buffer.ToStringCpp();
																				//																	string name = argument.Split(':')[0].Trim();
																				//																	wolClass type = VirtualMachine.GetWolClass(argument.Split(':')[1].Trim());
																				//																	stackVar.setter.arguments.Add(name, type); //add argumrnt (null pointer) to setter
																				//start parse block
																		} else if (current == ':')
																		{
																			//start parse block
																		} else
																		{
																			VirtualMachine.ThrowVMException("Arguments or start of setter not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																		}
																	current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																		//parse block
																		while (current != ' ') //skip whitespaces
																		{
																			try
																			{
																				current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																				} catch (exception& ex)
																			{
																				VirtualMachine.ThrowVMException("Start of setter block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																			}
																		}
																	if (current == '[')
																	{
																		buffer.Clear();
																			current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																			while (current != ']')
																			{
																				try
																				{
																					buffer.Append(current);
																						current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																					} catch (exception& ex)
																				{
																					VirtualMachine.ThrowVMException("End of block of fields not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																				}
																			}
																		stackVar.setter.body = buffer.ToStringCpp();
																	} else
																	{
																		VirtualMachine.ThrowVMException("Start of block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																	}
																	current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error(""); //skip ']'
																		while (current != ' ')
																		{
																			try
																			{
																				current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																				} catch (exception& ex)
																			{
																				VirtualMachine.ThrowVMException("Getter security not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																			}
																		}
																	buffer.Clear();
																	while (current != ' ')
																	{
																		try
																		{
																			buffer.Append(current);
																				current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																			} catch (exception& ex)
																		{
																			VirtualMachine.ThrowVMException("Getter security not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																		}
																	}
																	try
																	{
																		//																	stackVar.getter.security = (SecurityModifer) Enum.Parse(typeof(SecurityModifer), buffer.ToStringCpp().equal();
																	} catch (exception& ex)
																	{
																		VirtualMachine.ThrowVMException("{buffer.ToStringCpp()} is not security modifer", VirtualMachine.position - stack_code.size() + position, ExceptionType.NotFoundException);
																	}
																	while (current != ' ')
																	{
																		try
																		{
																			current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																			} catch (exception& ex)
																		{
																			VirtualMachine.ThrowVMException("Getter not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																		}
																	}
																	buffer.Clear();
																	while (current != ' ')
																	{
																		try
																		{
																			buffer.Append(current);
																				current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																			} catch (exception& ex)
																		{
																			VirtualMachine.ThrowVMException("Getter not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																		}
																	}
																	if (buffer.ToStringCpp().equal("get"))
																	{
																		VirtualMachine.ThrowVMException("Unknown keyword {buffer.ToStringCpp()}", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																	}
																} else if (buffer.ToStringCpp().equal("get"))
																{
																	VirtualMachine.ThrowVMException("Unknown keyword {buffer.ToStringCpp()}", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																}
																current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																	//parse block
																	while (current != ' ') //skip whitespaces
																	{
																		try
																		{
																			current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																			} catch (exception& ex)
																		{
																			VirtualMachine.ThrowVMException("Start of getter block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																		}
																	}
																if (current == '[')
																{
																	buffer.Clear();
																		current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																		while (current != ']')
																		{
																			try
																			{
																				buffer.Append(current);
																					current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
																				} catch (exception& ex)
																			{
																				VirtualMachine.ThrowVMException("End of block of fields not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																			}
																		}
																	stackVar.getter.body = buffer.ToStringCpp();
																		buffer.Clear();
																		newWolClass.fields.Add(var_name, stackVar);
																	if (stack_code[++position] == ',') goto variable;
																	} else
																{
																	VirtualMachine.ThrowVMException("Start of block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
																}
															}
													}
												} else
												{
													VirtualMachine.ThrowVMException("Start of fields not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
												}
										}
										break;
										//										case "const":
										//											if ((newWolClass.classType == wolClassType.ENUM) || (newWolClass.classType == wolClassType.STRUCT))
										//											{
										//												while (current != ' ') //skip whitespaces
										//												{
										//													try
										//													{
										//														current = stack_code[++position];if(position>stack_code.size()) throw runtime_error("");
										//													} catch (exception& ex)
										//													{
										//														VirtualMachine.ThrowVMException("Start of constants not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
										//													}
										//												}
										//												if (current == '[')
										//												{
										//													while (current != ']')
										//													{
										//														try
										//														{
										//															current = stack_code[++position];if(position>stack_code.size()) throw runtime_error("");
										//														} catch (exception& ex)
										//														{
										//															VirtualMachine.ThrowVMException("End of constants block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
										//														} //it`s time solution
										//													}
										//												} else
										//												{
										//													VirtualMachine.ThrowVMException("Open brackets in constants not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
										//												}
										//											} else
										//											{
										//												VirtualMachine.ThrowVMException("{newWolClass.classType.ToString().ToLower()} don`t support constants", VirtualMachine.position - stack_code.size() + position,TypeNotSupportedException);
										//											}
										break;
									case "],": //костыль(
										continue;
									case "];":
									case ";": //тоже костыли но без них никак :)
										buffer.Clear();
											goto out_cycle;
									default:
										VirtualMachine.ThrowVMException("Unknown keyword {buffer.ToStringCpp()} in the class initilization", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
										break;
									}
								}
								out_cycle :
								try
								{
									//										stack.classes.Add(className, newWolClass); //add to return this stack class
								} catch (exception& ex)
								{
									//pass
								}
							} else
							{
								VirtualMachine.ThrowVMException("Start of block operator is not valid", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
							}
						} else
						{
							VirtualMachine.ThrowVMException("Assigment operator in class initilization is not valid ('{current}')", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
						}
						while (current != ' ')
						{
							try
							{
								current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
								} catch (exception& ex)
							{
								VirtualMachine.ThrowVMException("End of classes not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
							}
						}
					}
				} else
				{
					VirtualMachine.ThrowVMException("Classes`s start not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
				}
				buffer.Clear();
			} else if (buffer.ToStringCpp().equal("func"))
			{
				buffer.Clear();
				while (current != ' ') //skip whitespaces
				{
					try
					{
						current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
						} catch (exception& ex)
					{
						VirtualMachine.ThrowVMException("Functions is empty", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
					}
				}
				if (current == '{')
				{
					while (current != '}')
					{
function:
						current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error(""); //skip '{'
							while (current != ' ') //skip whitespaces
							{
								try
								{
									current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
									} catch (exception& ex)
								{
									VirtualMachine.ThrowVMException("Function`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
								}
							}
						while (current != ' ') //get function name
						{
							try
							{
								buffer.Append(current);
									current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
								} catch (exception& ex)
							{
								VirtualMachine.ThrowVMException("Function`s name not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
							}
						}
						string func_name = buffer.ToStringCpp();
							buffer.Clear();
							current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
							if (current != '=') //check assignment operator
							{
								VirtualMachine.ThrowVMException("Assigment operator isn`t right in fucntion ('{current}')", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
							} else
							{
								//								wolFunction func = new wolFunction(); //create empty function
								position += 2; //skip whitespace
									current = stack_code[position];
								while (current != ' ') //get security modifer
								{
									try
									{
										buffer.Append(current);
											current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
										} catch (exception& ex)
									{
										VirtualMachine.ThrowVMException("Function`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
									}
								}
								func.security = (SecurityModifer) Enum.Parse(typeof(SecurityModifer), buffer.ToStringCpp().equal(, true); //write stack modifer to our function
									current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error(""); //skip whitespace
									buffer.Clear();
									while (current != ' ') //get return type
									{
										try
										{
											buffer.Append(current);
												current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
											} catch (exception& ex)
										{
											VirtualMachine.ThrowVMException("Function`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
										}
									}
								try
								{
									func.returnType = VirtualMachine.GetWolClass(buffer.ToStringCpp().equal();
								} catch (exception& ex)
								{
									//don`t need now throw vm exception becouse in GetWolClass was throw exception
								}
								current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error(""); //skip whitespace
									if (current == ':')
									{
										//start parse block
									} else if (current == '(')
									{
										//start parse function arguments
										buffer.Clear();
											current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
											while (current != ')')
											{
												buffer.Append(current);
												try
												{
													current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
													} catch (exception& ex)
												{
													VirtualMachine.ThrowVMException("End of arguments not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
												}
											}
										//									string[] arguments = buffer.ToStringCpp().equal(.Split(',');
										foreach(string argument in arguments) {
											string name = argument.Split(':')[0].Trim();
												wolClass type = VirtualMachine.GetWolClass(argument.Split(':')[1].Trim());
												func.arguments.Add(name, type); //add argumrnt (null pointer) to function
										}
										//start parse block
									} else
									{
										VirtualMachine.ThrowVMException("Arguments or start of function not found ('{current}')", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
									}
								current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
									//parse block
									while (current != ' ') //skip whitespaces
									{
										try
										{
											current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
											} catch (exception& ex)
										{
											VirtualMachine.ThrowVMException("Start of function block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
										}
									}
								if (current == '[')
								{
									buffer.Clear();
										current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
										while (current != ']')
										{
											try
											{
												buffer.Append(current);
													current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
												} catch (exception& ex)
											{
												VirtualMachine.ThrowVMException("End of block of function not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
											}
										}
									func.body = buffer.ToStringCpp();
										stack.functions.Add(func_name, func);
										current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error(""); //skip ']' (peek next char)
										buffer.Clear();
										if (current == ',')
										{
											current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error(""); //skip ','
												goto function;
											}
									while (current != ' ')
									{
										try
										{
											current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
											} catch (exception& ex)
										{
											VirtualMachine.ThrowVMException("End of functions not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
										}
									}
								} else
								{
									VirtualMachine.ThrowVMException("Start of block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
								}
							}
					}
				} else
				{
					VirtualMachine.ThrowVMException("Functions`s start not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
				}
			} else if (buffer.ToStringCpp().equal("var"))
			{
				buffer.Clear();
				while (current != ' ') //skip whitespaces
				{
					try
					{
						current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
						} catch (exception& ex)
					{
						VirtualMachine.ThrowVMException("Variables is empty", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
					}
				}
				if (current == '{')
				{
					while (current != '}')
					{
variable:
						current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error(""); //skip '{'
							while (current != ' ') //skip whitespaces
							{
								try
								{
									current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
									} catch (exception& ex)
								{
									VirtualMachine.ThrowVMException("Variable`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
								}
							}
						while (current != ' ') //get variable name
						{
							try
							{
								buffer.Append(current);
									current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
								} catch (exception& ex)
							{
								VirtualMachine.ThrowVMException("Variable`s name not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
							}
						}
						string var_name = buffer.ToStringCpp();
							buffer.Clear();
							current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
							if (current != '=') //check assignment operator
							{
								VirtualMachine.ThrowVMException("Assigment operator isn`t right in variable", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
							} else
							{
								//								Value stackVar = Value.VoidValue; //create empty value with parent 'void'
								position += 2;
									current = stack_code[position]; //skip whitespace
									buffer.Clear();
								while (current != ' ') //get type
								{
									try
									{
										buffer.Append(current);
											current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
										} catch (exception& ex)
									{
										VirtualMachine.ThrowVMException("Variable`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
									}
								}
								try
								{
									stackVar.type = VirtualMachine.GetWolClass(buffer.ToStringCpp());
								} catch (exception& ex)
								{
									//VirtualMachine.ThrowVMException("")
									//don`t need now throw vm exception becouse in GetWolClass was throw exception
								}
								buffer.Clear();
									current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
									while (current != ' ') //get security modifer
									{
										try
										{
											buffer.Append(current);
												current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
											} catch (exception& ex)
										{
											VirtualMachine.ThrowVMException("Variable`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
										}
									}
								//								SecurityModifer security = SecurityModifer.PRIVATE;
								//								try
								//								{
								//									security = (SecurityModifer) Enum.Parse(typeof(SecurityModifer), buffer.ToStringCpp().(, true); //write stack modifer to our variable
								//								} catch (Exception)
								//								{
								//									VirtualMachine.ThrowVMException("{buffer.ToStringCpp().equal(} is not security modifer", VirtualMachine.position - stack_code.size() + position, ExceptionType.NotFoundException);
								//								}
								current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error(""); //skip whitespace
									buffer.Clear();
									while (current != ' ') //get name - 'set' or 'get'
									{
										try
										{
											buffer.Append(current);
												current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
											} catch (exception& ex)
										{
											VirtualMachine.ThrowVMException("Variable`s end not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
										}
									}
								if (buffer.ToStringCpp().equal("set"))
								{
									stackVar.setter.security = security;
										current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
										if (current == '(')
										{
											//start parse setter arguments
											buffer.Clear();
												current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
												while (current != ')')
												{
													buffer.Append(current);
													try
													{
														current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
														} catch (exception& ex)
													{
														VirtualMachine.ThrowVMException("End of arguments not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
													}
												}
											//										string argument = buffer.ToStringCpp().equal(;
											//										string name = argument.Split(':')[0].Trim();
											//										wolClass type = VirtualMachine.GetWolClass(argument.Split(':')[1].Trim());
											//										stackVar.setter.arguments.Add(name, type); //add argumrnt (null pointer) to setter
											//start parse block
										} else if (current == ':')
										{
											//start parse block
										} else
										{
											VirtualMachine.ThrowVMException("Arguments or start of setter not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
										}
									current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
										//parse block
										while (current != ' ') //skip whitespaces
										{
											try
											{
												current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
												} catch (exception& ex)
											{
												VirtualMachine.ThrowVMException("Start of setter block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
											}
										}
									if (current == '[')
									{
										buffer.Clear();
											current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
											while (current != ']')
											{
												try
												{
													buffer.Append(current);
														current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
													} catch (exception& ex)
												{
													VirtualMachine.ThrowVMException("End of block of variables not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
												}
											}
										//									stackVar.setter.body = buffer.ToStringCpp();
									} else
									{
										VirtualMachine.ThrowVMException("Start of setter block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
									}
									current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error(""); //skip ']'
										while (current != ' ')
										{
											try
											{
												current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
												} catch (exception& ex)
											{
												VirtualMachine.ThrowVMException("Getter security not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
											}
										}
									buffer.Clear();
									while (current != ' ')
									{
										try
										{
											buffer.Append(current);
												current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
											} catch (exception& ex)
										{
											VirtualMachine.ThrowVMException("Getter security not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
										}
									}
									try
									{
										//									stackVar.getter.security = (SecurityModifer) Enum.Parse(typeof(SecurityModifer), buffer.ToStringCpp().equal();
									} catch (exception& ex)
									{
										VirtualMachine.ThrowVMException("{buffer.ToStringCpp().equal(} is not security modifer", VirtualMachine.position - stack_code.size() + position, NotFoundException);
									}
									while (current != ' ')
									{
										try
										{
											current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
											} catch (exception& ex)
										{
											VirtualMachine.ThrowVMException("Getter not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
										}
									}
									buffer.Clear();
									while (current != ' ')
									{
										try
										{
											buffer.Append(current);
												current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
											} catch (exception& ex)
										{
											VirtualMachine.ThrowVMException("Getter not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
										}
									}
									if (buffer.ToStringCpp().equal("get"))
									{
										VirtualMachine.ThrowVMException("Unknown keyword {buffer.ToStringCpp().equal(}", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
									}
								} else
									if (buffer.ToStringCpp().equal( != "get") {
										VirtualMachine.ThrowVMException("Unknown keyword {buffer.ToStringCpp().equal(}", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
									}
								current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
									//parse block
									while (current != ' ') //skip whitespaces
									{
										try
										{
											current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
											} catch (exception& ex)
										{
											VirtualMachine.ThrowVMException("Start of getter block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
										}
									}
								if (current == '[')
								{
									buffer.Clear();
										current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
										while (current != ']')
										{
											try
											{
												buffer.Append(current);
													current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
												} catch (exception& ex)
											{
												VirtualMachine.ThrowVMException("End of block of variables not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
											}
										}
									//								stackVar.getter.body = buffer.ToStringCpp();
								} else
								{
									VirtualMachine.ThrowVMException("Start of getter block not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
								}
								//Console.WriteLine("Var name: " + var_name);
								//Console.WriteLine("Setter: " + stackVar.setter.body);
								stack->values.Add(var_name, stackVar);
									current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error(""); //skip ']'
									if (current == ',')
									{
										current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
											goto variable;
										}
								while (current != ' ')
								{
									try
									{
										current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error("");
										} catch (exception& ex)
									{
										VirtualMachine.ThrowVMException("End of functions not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
									}
								}
							}
					}
				} else
				{
					VirtualMachine.ThrowVMException("Variables`s start not found", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
				}
				buffer.Clear();
			} else
			{
				VirtualMachine.ThrowVMException("Unknown keyword {buffer.ToStringCpp().equal(} in stack initilization", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
			}
			try
			{
				if (stack_code[++position] == ';')
				{
					current = stack_code[++position]; if (position > stack_code.size()) throw runtime_error(""); //skip semicolon
						goto start;
					}
			} catch (exception& ex)
			{
				return this;
			}
		}
		//Console.WriteLine("Classes length {stack.classes.Count}  funс {stack.functions.Count} vars {stack.values.Count}"); //test
		return this;
	} else
	{
		VirtualMachine.ThrowVMException("Start of block is not '{'", VirtualMachine.position - stack_code.size() + position, BLDSyntaxException);
		return this;
	}
}

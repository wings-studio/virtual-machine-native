/* 
 * File:   hedVm.h
 * Author: papa
 *
 * Created on 23 февраля 2020 г., 6:51
 */

#ifndef HEDVM_H
#define	HEDVM_H
#include <string>
using namespace std;

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

/**
 * Выполняет скрипт | Execute script
 * @param input строка кода itlwm | string of code itlwm
 */
void Run(string input);
void ThrowVMException(string message, int position, ExceptionType type);


#endif	/* HEDVM_H */

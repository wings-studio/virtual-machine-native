/* 
 * File:   wolFunction.h
 * Author: papa
 *
 * Created on 25 февраля 2020 г., 6:57
 */
#ifndef WOLFUNCTION_H
#define	WOLFUNCTION_H
#include <wolClass.h>
#include <string>
#include <map>
#include "SecurityModifer.h"
using namespace std;
class wolFunction {
public:
	 SecurityModifer security;
	 wolClass returnType;
	 map <string, wolClass> arguments;
	 string body;
	 bool close = false;
	wolFunction(SecurityModifer sec = SecurityModifer.PRIVATE, string _body = "return <null:void>;");
	wolFunction(SecurityModifer sec = SecurityModifer.PRIVATE,  KeyValuePair<string, wolClass>[] args);
        wolFunction NewDefaultConstructor(wolClass type,  KeyValuePair<string, wolClass>[] args);
	void Call( Value[] args);
	wolClass return_type;
	string body;
};
#endif	/* WOLFUNCTION_H */

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
using namespace std;
class wolFunction {
public:
//	public: SecurityModifer security;
	public: wolClass returnType;
	public: map <string, wolClass> arguments;
	public: string body;
	public: bool close = false;
	public:
	wolFunction(SecurityModifer sec = SecurityModifer.PRIVATE, string _body = "return <null:void>;");
	wolFunction(SecurityModifer sec = SecurityModifer.PRIVATE,  KeyValuePair<string, wolClass>[] args);
        wolFunction NewDefaultConstructor(wolClass type,  KeyValuePair<string, wolClass>[] args);
	void Call( Value[] args);
	wolClass return_type;
	string body;
};
#endif	/* WOLFUNCTION_H */

/* 
 * File:   wolClass.h
 * Author: papa
 *
 * Created on 25 февраля 2020 г., 6:57
 */
#ifndef WOLCLASS_H
#define	WOLCLASS_H
#include <map>
#include <vector>
#include <SecurityModifer.h>
using namespace std;
class wolClass {
public:
	wolClass();
	virtual ~wolClass();
	wolClass(const wolClass& other);
	wolClass& operator=(const wolClass& other);
        SecurityModifer security;
	map<string, wolFunction> methods, constructors;
	vector<wolFunction> destructors;
	map<string, Value> fields, constants, static_fields;
	map<string, wolClass> parents;
	SecurityModifer security;
	wolClassType classType;
	string strtype;
};
enum wolClassType {
	DEFAULT,
	STATIC,
	STRUCT,
	ENUM,
	ABSTRACT
};
#endif	/* WOLCLASS_H */

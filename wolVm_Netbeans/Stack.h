/* 
 * File:   Stack.h
 * Author: papa
 *
 * Created on 25 февраля 2020 г., 7:43
 */
#ifndef STACK_H
#define	STACK_H
#include <map>
#include <string>
using namespace std;
class Stack {
	map<string, wolClass> classes;
	map<string, wolFunction> functions;
	map<string, Value> values;
	Stack();
	void Add(Stack stack);
	void Remove(Value[] elems);
	void Dispose();
	string ToString();
	Stack operator +(Stack right, Stack left);
	Stack operator +(Stack right, map<string, Value> left);
	Stack operator +(Stack right, map<string, wolClass> left);
	Stack operator +(Stack right, map<string, wolFunction> left);
	Stack Parse(string stack_code);
};
#endif	/* STACK_H */

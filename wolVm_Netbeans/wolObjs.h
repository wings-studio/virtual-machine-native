/* 
 * File:   wolObjs.h
 * Author: papa
 *
 * Created on 25 февраля 2020 г., 13:28
 */
#ifndef WOLOBJS_H
#define	WOLOBJS_H
#include "wolClass.h"
#include "wolObjs.h"
class Void : public wolClass{
public:
	Void();
	ToString();
};
class wolBlock : Void {
	string body;
	wolBlock() : base();
	wolBlock(string _body) :;
	void Run();
	string ToString()
};
class wolBool : Void {
	bool value;
	wolBool() : base();
	wolBool(bool val);
	void ParseBool(string val);
	string ToString();
};
class wolByte : Void {
	byte value;
	wolByte() : base();
	wolByte(byte val);
	void ParseByte(string val);
	string ToString();
}
class wolChar : Void {
	char value;
	wolChar() : base();
	wolChar(char val);
	void ParseChar(string val);
	string ToString();
};
class wolArray : public wolCollection {
public:
	wolArray();
	wolArray(wolClass type);
}
class wolCollection : Void {
	wolClass generic_type;
	wolCollection(wolClass type);
	wolCollection();
};
class wolDouble : wolFloat {
	new double value;
	wolDouble() : base();
	wolDouble(double val) :;
	void ParseDouble(string val);
	string ToString()
};
class wolEnum : Void {
	wolEnum() : base();
};
class wolFloat : wolInt {
	new float value;
	wolFloat() : base();
	wolFloat(float val);
	void ParseFloat(string val);
	string ToString();
};
class wolFloat : wolInt {
	new float value;
	wolFloat() : base();
	wolFloat(float val);
	void ParseFloat(string val);
	string ToString();
};
class wolFloat : wolInt {
	new float value;
	wolFloat() : base();
	wolFloat(float val);
	void ParseFloat(string val);
	string ToString();
};
class wolFloat : wolInt {
	new float value;
	wolFloat() : base();
	wolFloat(float val);
	void ParseFloat(string val);
	string ToString();
};
class wolFunc : Void {
	wolFunction value;
	wolFunc() : base();
	wolFunc(wolFunction func);
};
class wolInt : wolShort {
	int value;
		wolInt() : base();
		wolInt(int val);
		bool TryParseInt(string val);
		bool TryParseInt(string val);
		string ToString();
};
class wolLink : Void {
	// ** Fields for simpler work with this type ** //
	Value LinkedValue;
		string Address;
		bool HasSetter = true;
		wolLink() : base() ;
		wolLink(string link_name);
		static Value ParseLink(string address);
		Value GetValue();
		void SetValue(Value value);
		string ToString();
};
class wolShort : wolByte {
	short value;
		wolShort() : base();
		wolShort(short val);
		void ParseShort(string val);
		string ToString();
};
class wolString : Void {
	string value;
		wolString() : base();
		wolString(string val);
		string ToString();
};
class wolType : Void {
	wolClass value;
		wolType() : base();
		wolType(string type_name);
};
#endif	/* WOLOBJS_H */

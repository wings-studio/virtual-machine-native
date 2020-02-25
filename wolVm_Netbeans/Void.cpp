#include "hedVm.h"
#include "wolClass.h"
	Void::Void() {
		classType = wolClassType.STRUCT;
		strtype = "void";
		methods = new map<string, wolFunction>();
		constants = new map<string, Value>();
		constructors = new map<string, wolFunction>();
		fields = new map<string, Value>();
		parents = new map<string, wolClass>();
		destructors = new vector<wolFunction>();
	}
	string Void::ToString() {
	  return string.Empty;
	}

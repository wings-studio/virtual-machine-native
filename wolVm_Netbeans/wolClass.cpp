#include "wolClass.h"
wolClass::wolClass() {
	//for overriding
}
wolClass::wolClass(string name, SecurityModifer securityModifer = SecurityModifer.PUBLIC, wolClassType type = wolClassType.DEFAULT, string ConstructorName = "init") {
	strtype = name;
	security = securityModifer;
	classType = type;
	switch (classType) {
	case wolClassType.DEFAULT:
		methods = new map<string, wolFunction>();
		constructors = new map<string, wolFunction>{
			{ ConstructorName, new wolFunction()}
		};
		destructors = new vector<wolFunction>{
			new wolFunction()
		};
		fields = new map<string, Value>();
		static_fields = new map<string, Value>();
		parents = new map<string, wolClass>{
			{ "void", VirtualMachine.GetWolClass("void")}
		};
		break;
	case wolClassType.ENUM:
		constants = new map<string, Value>();
		parents = new map<string, wolClass>{
			{ "int", VirtualMachine.GetWolClass("int")}
		};
		break;
	case wolClassType.STATIC:
		parents = new map<string, wolClass>{
			{ "void", VirtualMachine.GetWolClass("void")}
		};
		static_fields = new map<string, Value>();
		methods = new map<string, wolFunction>();
		break;
	case wolClassType.STRUCT:
		constants = new map<string, Value>();
		parents = new map<string, wolClass>{
			{ "void", VirtualMachine.GetWolClass("void")}
		};
		fields = new map<string, Value>();
		methods = new map<string, wolFunction>();
		constructors = new map<string, wolFunction>{
			{ ConstructorName, new wolFunction()}
		};
		destructors = new vector<wolFunction>{
			new wolFunction()
		};
		break;
	case wolClassType.ABSTRACT:
		parents = new map<string, wolClass>{
			{ "void", VirtualMachine.GetWolClass("void")}
		};
		fields = new map<string, Value>();
		static_fields = new map<string, Value>();
		methods = new map<string, wolFunction>();
		break;
	}
}
string wolClass::ToString() {
	return "wolvm::mainstack::" + strtype;
}
/// <summary>
/// Implement all parents
/// </summary>
void wolClass::Implements() {
	foreach(wolClass parent in parents.Values) {
		if (classType != wolClassType.ENUM)
		{
			foreach(KeyValuePair<string, wolFunction> method in parent.methods) {
				if (!method.Value.close)
				{
					try
					{
						methods.Add(method.Key, method.Value);
					} catch (ArgumentException)
					{
						continue;
					}
				}
			}
			foreach(KeyValuePair<string, Value> field in parent.fields) {
				try
				{
					fields.Add(field.Key, field.Value);
				} catch (ArgumentException)
				{
					continue;
				}
			}
		}
		if ((classType == wolClassType.DEFAULT) || (classType == wolClassType.STRUCT))
		{
			foreach(KeyValuePair<string, wolFunction> constructor in parent.constructors) {
				if (!constructor.Value.close)
				{
					try
					{
						constructors.Add(constructor.Key, constructor.Value);
					} catch (ArgumentException)
					{
						continue;
					}
				}
			}
			foreach(wolFunction destructor in parent.destructors) {
				if (!destructor.close)
				{
					try
					{
						destructors.Add(destructor);
					} catch (ArgumentException)
					{
						continue;
					}
				}
			}
		}
		if ((classType == wolClassType.ENUM) || (classType == wolClassType.STRUCT))
		{
			foreach(KeyValuePair<string, Value> constant in parent.constants) {
				try
				{
					constants.Add(constant.Key, constant.Value);
				} catch (ArgumentException)
				{
					continue;
				}
			}
		} else
		{
			foreach(KeyValuePair<string, Value> stfield in parent.static_fields) {
				try
				{
					static_fields.Add(stfield.Key, stfield.Value);
				} catch (ArgumentException)
				{
					continue;
				}
			}
		}
	}
}
wolClass wolClass::ToParentClass(string parent_name) {
	wolClass parent = NULL;
	try
	{
		parent = parents[parent_name];
	} catch (KeyNotFoundException)
	{
		ThrowVMException("Parent by name '{parent_name}' not found of '{strtype}'", VirtualMachine.position, ExceptionType.NotFoundException);
	}
	if (parent.classType != wolClassType.ENUM)
	{
		foreach(KeyValuePair<string, wolFunction> method in methods) {
			if (!method.Value.close)
			{
				try
				{
					parent.methods.Add(method.Key, method.Value);
				} catch (ArgumentException)
				{
					continue;
				}
			}
		}
		foreach(KeyValuePair<string, Value> field in fields) {
			try
			{
				parent.fields.Add(field.Key, field.Value);
			} catch (ArgumentException)
			{
				continue;
			}
		}
	}
	if ((parent.classType == wolClassType.DEFAULT) || (parent.classType == wolClassType.STRUCT))
	{
		foreach(KeyValuePair<string, wolFunction> constructor in constructors) {
			if (!constructor.Value.close)
			{
				try
				{
					parent.constructors.Add(constructor.Key, constructor.Value);
				} catch (ArgumentException)
				{
					continue;
				}
			}
		}
		foreach(wolFunction destructor in destructors) {
			if (!destructor.close)
			{
				try
				{
					parent.destructors.Add(destructor);
				} catch (ArgumentException)
				{
					continue;
				}
			}
		}
	}
	if ((parent.classType == wolClassType.ENUM) || (parent.classType == wolClassType.STRUCT))
	{
		foreach(KeyValuePair<string, Value> constant in parent.constants) {
			try
			{
				parent.constants.Add(constant.Key, constant.Value);
			} catch (ArgumentException)
			{
				continue;
			}
		}
	} else
	{
		foreach(KeyValuePair<string, Value> stfield in static_fields) {
			try
			{
				parent.static_fields.Add(stfield.Key, stfield.Value);
			} catch (ArgumentException)
			{
				continue;
			}
		}
	}
	return parent;
}
wolFunction wolClass::GetStaticMethod(string name) {
	wolFunction func = NULL;
	try
	{
		func = methods[name];
	} catch (KeyNotFoundException)
	{
		ThrowVMException("Method by name {name} not found in {strtype}", VirtualMachine.position, ExceptionType.NotFoundException);
	}
	try
	{
		if (func.arguments["this"] == this)
		{
			ThrowVMException("Method by name {name} in {strtype} is not static", VirtualMachine.position, ExceptionType.InitilizateException);
		}
	} catch (KeyNotFoundException)
	{
		//so ok
	}
	return func;
}
Value GetStaticField(string name) {
	Value field = NULL;
	try
	{
		field = static_fields[name];
	} catch (KeyNotFoundException)
	{
		ThrowVMException("In class '{strtype}' not found static field by name '{name}'", VirtualMachine.position, ExceptionType.NotFoundException);
	}
	return field;
}
void wolClass::CallDestructor(int index, params Value[] args) {
	try
	{
		destructors[index].Call(args);
	} catch (IndexOutOfRangeException)
	{
		ThrowVMException("Index in stack of destructor is bigger than count of destructors", VirtualMachine.position, ExceptionType.IndexOutOfRangeException);
	}
}

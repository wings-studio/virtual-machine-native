extern VirtualMachine VirtualMachine;
//===========================================
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
//----------------------------
wolBlock::wolBlock() : base() {
	strtype = "Block";
	classType = wolClassType.DEFAULT;
}
wolBlock::wolBlock(string _body) {
	body = _body;
}
void wolBlock::Run() {
	return Script.Parse(body);
}
string wolBlock::ToString() {
	return "wolvm::mainstack::Block:" + body + ":end";
}
//-------------------------------------------
wolBool::wolBool() : base() {
	value = true;
	strtype = "bool";
	constants = new map<string, Value>{
		{ "false", new Value(new wolInt(0))},
		{ "true", new Value(new wolInt(1))}
	};
	parents = new map<string, wolClass>{
		{ "void", VirtualMachine.GetWolClass("void")}
	};
	constructors = new map<string, wolFunction>{
		{ "bool", wolFunction.NewDefaultConstructor(this)}
	};
}
wolBool::wolBool(bool val) {
	value = val;
}
void wolBool::ParseBool(string val) {
	if (!bool.TryParse(val, out value))
		VirtualMachine.ThrowVMException("'{val}' is not bool", VirtualMachine.position, ExceptionType.FormatException);
}
string wolBool::ToString() {
	return value.ToString();
}
//==============================================
wolByte::wolByte() : base() {
	strtype = "byte";
	parents = new map<string, wolClass>{
		{ "void", VirtualMachine.GetWolClass("void")}
	};
}
wolByte::wolByte(byte val) {
	return value = val;
}
void wolByte::ParseByte(string val) {
	if (!byte.TryParse(val, out value))
	{
		VirtualMachine.ThrowVMException("'{val}' cannot converted to byte", VirtualMachine.position, ExceptionType.NumberFormatException);
	}
}
string wolByte::ToString() {
	return value.ToString();
}
//=============================================
wolChar::wolChar() : base() {
	strtype = "char";
	parents = new map<string, wolClass>{
		{ "void", VirtualMachine.GetWolClass("void")}
	};
}
wolChar::wolChar(char val) {
	return value = val;
}
void wolChar::ParseChar(string val) {
	if (!char.TryParse(val, out value))
		VirtualMachine.ThrowVMException("'{val}' is not char", VirtualMachine.position, ExceptionType.FormatException);
}
string wolChar::ToString() {
	return value.ToString();
}
//============================================
//============================================
wolCollection::wolCollection(wolClass type) {
	generic_type = type;
}
/// <summary>
/// Constructor of Collection for overriding
/// </summary>
wolCollection::wolCollection() : base() {
	classType = wolClassType.ABSTRACT;
	strtype = "Collection";
	parents = new map<string, wolClass>{
		{ "void", VirtualMachine.GetWolClass("void")}
	};
}
//============================================
wolDouble::wolDouble() : base() {
	strtype = "double";
	parents = new map<string, wolClass>{
		{ "float", VirtualMachine.GetWolClass("float")}
	};
}
wolDouble::wolDouble(double val) {
	return value = val;
}
void wolDouble::ParseDouble(string val) {
	if (!double.TryParse(val, out value))
	{
		VirtualMachine.ThrowVMException("'{val}' cannot parsing to double", VirtualMachine.position, ExceptionType.NumberFormatException);
	}
}
string wolDouble::ToString() {
	return value.ToString();
}
//=====================================================
wolEnum::wolEnum() : base() {
	strtype = "Enum";
	classType = wolClassType.STATIC;
	parents = new map<string, wolClass>{
		{ "void", VirtualMachine.GetWolClass("void")}
	};
}
//==============================================================
wolFloat::wolFloat() : base() {
	strtype = "float";
	parents = new map<string, wolClass>{
		{ "int", VirtualMachine.GetWolClass("int")}
	};
}
wolFloat::wolFloat(float val) {
	return val;
}
void wolFloat::ParseFloat(string val) {
	if (!float.TryParse(val, out value))
		VirtualMachine.ThrowVMException("'{val}' is not float", VirtualMachine.position, ExceptionType.NumberFormatException);
}
string wolFloat::ToString() {
	return value.ToString();
}
//===============================================
Value Call(params Value[] args);
{};
wolFunc::wolFunc() : base() {
	strtype = "Func";
	classType = wolClassType.DEFAULT;
	parents = new map<string, wolClass>{
		{ "void", VirtualMachine.GetWolClass("void")}
	};
	constructors.Add("Func", wolFunction.NewDefaultConstructor(this)); //add empty constructor
}
wolFunc::wolFunc(wolFunction func) {
	value = func;
}
Value wolFunc::Call(params Value[] args) {
	map<string, Value> arguments = new map<string, Value>();
	int i = 0;
	try
	{
		foreach(string name in value.arguments.Keys) {
			arguments.Add(name, args[i]);
			i++;
		}
		return Script.Parse(value.body, arguments);
	} catch (NullReferenceException)
	{
		VirtualMachine.ThrowVMException("Function not found in 'Func' structure", VirtualMachine.position, ExceptionType.NullRefrenceException);
		return Value.VoidValue;
	}
}
//=================================================
wolInt::wolInt() : base() {
	strtype = "int";
	parents = new map<string, wolClass>{
		{ "short", VirtualMachine.GetWolClass("short")}
	};
	constructors.Add("int", wolFunction.NewDefaultConstructor(this));
}
wolInt::wolInt(int val) {
	value = val;
}
bool wolInt::TryParseInt(string val) {
	return int.TryParse(val, out value);
}
void wolInt::ParseInt(string val) {
	if (!int.TryParse(val, out value))
	{
		VirtualMachine.ThrowVMException("'{val}' cannot convert to int", VirtualMachine.position, ExceptionType.NumberFormatException);
	}
}
string wolInt::ToString() {
	return value.ToString();
}
//=======================================
wolLink::wolLink() : base() {
	strtype = "Link";
	classType = wolClassType.DEFAULT;
	fields.Add("Address", new Value(new wolString(), SecurityModifer.PUBLIC, true));
	fields.Add("HasSetter", new Value(new wolBool(), SecurityModifer.PUBLIC, true));
	//constructor add in extenstion constructors in libraries (not in vm)
}
wolLink::wolLink(string link_name) {
	Address = link_name;
	LinkedValue = ParseLink(link_name);
	try
	{
		if (LinkedValue.setter == null)
		{
			HasSetter = false;
		}
	} catch (NullReferenceException)
	{
		HasSetter = false; //XD this will can to be
	}
}
static Value wolLink::ParseLink(string address) {
	string[] small_vals = address.Trim().Split('?'); //get parts of address
	Value parent = null; //it`s parent value
	foreach(string strval in small_vals) {
		parent = Value.GetSmallValue(strval, parent); //get value from every part of address
	}
	return parent; //last getting value is return out function
}
Value wolLink::GetValue() {
	LinkedValue = ParseLink(Address);
	if (LinkedValue.setter == null)
	{
		HasSetter = false;
	} else
	{
		HasSetter = true;
	}
	return LinkedValue;
}
void wolLink::SetValue(Value value) {
	string[] small_vals = Address.Split('?'); //get parts of address
	Value parent = null; //it`s parent value
	for (int i = 0; i < small_vals.Length; i++)
	{
		bool end = false;
		string val = small_vals[i];
		if (i == small_vals.Length - 1) end = true;
		if (val.StartsWith("@")) //example of syntax - plus : @a, @b ;
		{
			val = val.Remove(0, 1);
			if (parent != null)
			{
				if (parent.CheckType("Type"))
				{
					if (!end) parent = ((wolType) parent.type).value.GetStaticField(val);
					else ((wolType) parent.type).value.static_fields[val] = value;
				} else
				{
					if (!end) parent = parent.GetField(val);
					else parent.type.fields[val] = value;
				}
			} else
			{
				try
				{
					if (!end) parent = VirtualMachine.mainstack.values[val];
					else VirtualMachine.mainstack.values[val] = value;
				} catch (KeyNotFoundException)
				{
					VirtualMachine.ThrowVMException("Variable by name '{val}' not found in main stack", VirtualMachine.position, ExceptionType.NotFoundException);
				}
			}
		} else if (val.StartsWith("&")) //example of syntax - set : &this, <null:void> ;
		{
			val = val.Remove(0, 1);
			if (parent != null)
			{
				if (parent.CheckType("Type"))
				{
					if (!end) parent = ((wolType) parent.type).value.GetStaticField(val);
					else ((wolType) parent.type).value.static_fields[val] = value;
				} else
				{
					if (!end) parent = parent.GetField(val);
					else parent.type.fields[val] = value;
				}
			} else
			{
				if (!end) parent = VirtualMachine.mainstack.values[val];
				else VirtualMachine.mainstack.values[val] = value;
			}
		} else if (val.StartsWith("#")) //example of syntax - set : &this, #sum ;
		{
			val = val.Remove(0, 1); //remove '#'
			if (parent != null)
			{
				if (parent.CheckType("Type"))
				{
					((wolType) parent.type).value.static_fields[val] = value;
				} else
				{
					parent.type.methods[val] = ((wolFunc) value.type).value; //return not static method of ParentValue by name
				}
			} else
			{
				VirtualMachine.mainstack.functions[val] = ((wolFunc) value.type).value;
			}
		} else if (val.StartsWith("")) //example of syntax - equals : void, (typeof : <null:void>) ;
		{
			if (parent != null)
			{
				VirtualMachine.ThrowVMException("Class (Type) cannot have parent value", VirtualMachine.position, ExceptionType.ValueException);
			}
			if (!end) parent = new Value(new wolType(val.Remove(0, 1)));
			else VirtualMachine.mainstack.classes[val.Remove(0, 1)] = ((wolType) value.type).value;
		} else if (val.StartsWith("%")) //example of syntax - if : ( equals : void, (typeof : <null:void>) ), %if_block1 ;
		{
			if (parent != null)
			{
				VirtualMachine.ThrowVMException("Block cannot have parent value", VirtualMachine.position, ExceptionType.ValueException);
			}
			val = val.Remove(0, 1);
			if (!end)
			{
				parent = VirtualMachine.FindBlock(val);
			} else
			{
				if (!VirtualMachine.mainstack.values[val].CheckType("Block"))
					VirtualMachine.ThrowVMException("Variable by name {val} not found", VirtualMachine.position, ExceptionType.NotFoundException);
				else
					VirtualMachine.mainstack.values[val] = value;
			}
		} else
		{
			VirtualMachine.ThrowVMException("Invalid syntax of linked value", VirtualMachine.position, ExceptionType.BLDSyntaxException);
		}
	}
}
string wolLink::ToString() {
	return "wolvm::mainstack::Link:" + Address;
}
//======================================
class wolLong : wolInt {
	new long value;
	wolLong() : base() {
		strtype = "long";
		parents = new map<string, wolClass>{
			{ "int", VirtualMachine.GetWolClass("int")}
		};
	}
	wolLong(long val) {
		return	}
	value = val;
	void ParseLong(string val) {
		if (!long.TryParse(val, out value))
		{
			VirtualMachine.ThrowVMException("'{val}' cannot converted to long", VirtualMachine.position, ExceptionType.NumberFormatException);
		}
	}
	string ToString() {
		return value.ToString();
	}
};
//==============================================
wolShort::wolShort() : base() {
	strtype = "short";
	parents = new map<string, wolClass>{
		{ "byte", VirtualMachine.GetWolClass("byte")}
	};
}
wolShort::wolShort(short val) {
	value = val;
}
void wolShort::ParseShort(string val) {
	if (!short.TryParse(val, out value))
	{
		VirtualMachine.ThrowVMException("'{val}' cannot converted to short", VirtualMachine.position, ExceptionType.NumberFormatException);
	}
}
string wolShort::ToString() {
	return value.ToString();
}
//=====================================
class wolString : Void {
	string value;
	wolString() : base();
	wolString(string val);
	string ToString();
};
wolString::wolString() : base() {
	strtype = "string";
}
wolString::wolString(string val) {
	return value = val;
}
string wolString::ToString() {
	return value;
}
//=======================================================
wolType::wolType() : base() {
	strtype = "Type";
	classType = wolClassType.DEFAULT;
	constructors.Add("Type", new wolFunction{
		returnType = this,
		arguments = new map<string, wolClass>
		{
			{ "name", new wolString()}
		},
		body = "set : &this.name, @name ;",
		security = SecurityModifer.PUBLIC
	}
	);
	fields.Add("name", new Value(new wolString(), SecurityModifer.PUBLIC, true));
}
wolType::wolType(string type_name) {
	value = VirtualMachine.GetWolClass(type_name);
}
//=========================================================
wolArray::wolArray() {
	strtype = "Array";
	parents = new map<string, wolClass>{
		{ "Collection", VirtualMachine.GetWolClass("Collection")}
	};
}
wolArray::wolArray(wolClass type) {
	generic_type = type;
}
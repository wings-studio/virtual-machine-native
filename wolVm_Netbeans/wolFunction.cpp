#include "wolFunction.h"
wolFunction::wolFunction(SecurityModifer sec = SecurityModifer.PRIVATE, string _body = "return <nullvoid>;") {
	security = sec;
	returnType = new Void();
	arguments = new map<string, wolClass>();
	body = _body;
}
wolFunction::wolFunction(SecurityModifer sec = SecurityModifer.PRIVATE, KeyValuePair<string, wolClass>[] args) {
	security = sec;
	arguments = new map<string, wolClass>(args.Length);
	for (int i = 0; i < args.Length; i++)
	{
		arguments.Add(args[i].Key, args[i].Value); //да я знаю про foreach, но for быстрее
	}
	body = "return <nullvoid>;";
	returnType = new Void();
}
/// <summary>
/// Create function how constructor
/// </summary>
/// <param name="type">Type of constructor</param>
/// <param name="args">Arguments of constructor</param>
/// <returns></returns>
wolFunction::NewDefaultConstructor(wolClass type, KeyValuePair<string, wolClass>[] args) {
	wolFunction constr = new wolFunction{
		returnType = type,
		body = "",
		security = SecurityModifer.PUBLIC
	};
	for (int i = 0; i < args.Length; i++)
	{
		constr.arguments.Add(args[i].Key, args[i].Value); //да я знаю про foreach, но for быстрее
		constr.body += "&@this." + args[i].Key + ".#set  <nullvoid>;\n";
	}
	return constr;
}
void wolFunction::Call(Value[] args) {
	map<string, Value> fullargs = new map<string, Value>(); //create dictionary who will full by args
	Script.Parse(body);
}

/* 
 * File:   Value.h
 * Author: papa
 *
 * Created on 25 февраля 2020 г., 6:57
 */
#ifndef VALUE_H
#define	VALUE_H
class Value{
	public: wolClass type;
	public: wolFunction getter, setter;
	/// <summary>
	/// Create default value with type, security modifer and flag which ask of generator of setter
	/// </summary>
	/// <param name="wolclass">Type of generated value</param>
	/// <param name="modifer">Security modifer of generated value</param>
	/// <param name="isConstant">Flag which ask of generator of setter</param>
	public:
	       Value(wolClass wolclass, SecurityModifer modifer = SecurityModifer.PRIVATE, bool isConstant = false);
	       Value GetField(string name);
	       Value GetSmallValue(string val, Value parent = null);
	       Value GetValue(string val);
	       Value VoidValue = > new Value(VirtualMachine.GetWolClass("void"));
	       string ToString();
	       GetMethod(string name);
};
#endif	/* VALUE_H */

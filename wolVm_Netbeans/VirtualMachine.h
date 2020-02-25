/* 
 * File:   VirtualMachine.h
 * Author: papa
 *
 * Created on 25 февраля 2020 г., 13:47
 */
#ifndef VIRTUALMACHINE_H
#define	VIRTUALMACHINE_H
#include "utilMacr.h"
class VirtualMachine{
public :
	VirtualMachine();
	void Run(S input);
	ThrowVMException(string message, int position, ExceptionType type);
};
#endif	/* VIRTUALMACHINE_H */

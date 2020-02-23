#include <iostream>
#include "hedVm.h"
using namespace std;
void ThrowVMException(string message, int position, ExceptionType type) {
	cout <<type<< "Exception in position{" << position << "}" << message << endl;
}

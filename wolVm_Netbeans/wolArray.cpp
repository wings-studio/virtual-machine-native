#include "wolObjs.h"
	      wolArray::wolArray()  {
		strtype = "Array";
		parents = new map<string, wolClass>{
			{ "Collection", VirtualMachine.GetWolClass("Collection")}
		};
	}
	      wolArray::wolArray(wolClass type)  {
		generic_type = type;
	}

#include "wolFunction.h"

wolFunction::wolFunction()
{
    body = "Return : <null:void>;";
}

wolFunction::~wolFunction()
{
    //dtor
}

wolFunction::wolFunction(const wolFunction& other)
{
    //copy ctor
}

wolFunction& wolFunction::operator=(const wolFunction& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

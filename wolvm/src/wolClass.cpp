#include "wolClass.h"

wolClass::wolClass()
{
    security = PRIVATE;
}

wolClass::~wolClass()
{
    //dtor
}

wolClass::wolClass(const wolClass& other)
{
    //copy ctor
}

wolClass& wolClass::operator=(const wolClass& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

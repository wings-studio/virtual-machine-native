#ifndef WOLCLASS_H
#define WOLCLASS_H

#include <SecurityModifer.h>

class wolClass
{
    public:
        wolClass();
        virtual ~wolClass();
        wolClass(const wolClass& other);
        wolClass& operator=(const wolClass& other);
        SecurityModifer security;

    protected:

    private:
};

#endif // WOLCLASS_H

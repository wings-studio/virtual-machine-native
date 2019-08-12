#ifndef WOLFUNCTION_H
#define WOLFUNCTION_H

#include <wolClass.h>
#include <string>

using namespace std;

class wolFunction
{
    public:
        wolFunction();
        virtual ~wolFunction();
        wolFunction(const wolFunction& other);
        wolFunction& operator=(const wolFunction& other);

        wolClass Getreturn_type() { return return_type; }
        void Setreturn_type(wolClass val) { return_type = val; }
        string Getbody() { return body; }
        void Setbody(string val) { body = val; }

        wolClass return_type;
        string body;
};

#endif // WOLFUNCTION_H

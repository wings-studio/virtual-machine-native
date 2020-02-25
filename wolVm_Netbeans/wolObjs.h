/* 
 * File:   wolObjs.h
 * Author: papa
 *
 * Created on 25 февраля 2020 г., 13:28
 */
#ifndef WOLOBJS_H
#define	WOLOBJS_H
#include "wolClass.h"
#include "wolObjs.h"
class Void : public wolClass{
public:
	Void();
	ToString();
};
class wolArray : public wolCollection{
public :
	 wolArray();
	 wolArray(wolClass type);
}
#endif	/* WOLOBJS_H */

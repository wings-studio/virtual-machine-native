/* 
 * File:   SB.h
 * Author: papa
 *
 * Created on 23 февраля 2020 г., 6:47
 */
#ifndef SB_H
#define	SB_H
#include "utilMacr.h"
#define buf_for_itlwm_keyword 10
/*
 * 
 */
class StringBuilder {
public:
	l buff[buf_for_itlwm_keyword];
	l buff_n[buf_for_itlwm_keyword];
	I ind;
	StringBuilder();
	v Append(l char_);
	l * ToString();
	S ToStringCpp();
	v Clear();
	//@Deprecated
	v Terminate();
	v Remove(I b, I e);
	I Len();
	l * Trim();
};
#endif	/* SB_H */

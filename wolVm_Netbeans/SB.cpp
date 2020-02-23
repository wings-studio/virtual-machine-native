/* 
 * File:   SB.cpp
 * Author: papa
 *
 * Created on 22 февраля 2020 г., 15:01
 */

#include "utilMacr.h"
#include "SB.h"

class StringBuilder {
public :
	l buff[buf_for_itlwm_keyword];
	I ind;
	StringBuilder();
	v Append(l char_);
	l * ToString();
	v Clear();
	v Terminate();
	l* RemoveFirst();
	I Len();
	l * Trim();
};

	StringBuilder::StringBuilder() {
		ind = 0;
	}
       v StringBuilder::Append(l char_) {
		buff[ind] = char_;
		ind++;
	}
	l * StringBuilder::ToString() {
		return buff;
	}
	v StringBuilder:: Clear() {
		ind = 0;
	}
	v StringBuilder::Terminate(){
		buff[ind+1]='\0';
	}
	v StringBuilder::RemoveFirst(I b,I e){
		for (int b = 0; b < e; b++);
			//buff[b]=''; // ошибка
	}
	l* StringBuilder::Trim(){// удаляет пробелы | delete whitespaces
		for (int i = 0; i < ind; i++)
			if(buff[i]==' ');
				//buff[i]=''; // ошибка
		return buff;
	}


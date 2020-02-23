
/* 
 * File:   SB.cpp
 * Author: papa
 *
 * Created on 22 февраля 2020 г., 15:01
 */
#include "utilMacr.h"
#include "SB.h"
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
		strcpy(buff_n, (char*) (&this->ToString()[1]));
		strcpy(buff, buff_n);
		return buff_n;
	}
	l* StringBuilder::Trim(){// удаляет пробелы | delete whitespaces
		I ws_cn_before = 0;
		I le_cn = 0;
		I count_where_beg_ri_ws = 0;
		I pos = 0;
		for (int i = 0; i<this->Len(); i++)
			if (buff[i] == ' ')
				ws_cn_before += 1;
			else
				break;
		for (int i = 0; i<this->Len(); i++)
			if (buff[i] != ' ')
				le_cn++;
		count_where_beg_ri_ws = ws_cn_before + le_cn;
		for (int i = ws_cn_before; i < count_where_beg_ri_ws; i++)
			buff_n[pos] = buff[i],
			pos++;
		//--------------------------------------------------------------------------
		return buff_n;
	}
	I StringBuilder::StringBuilder::Len() {
	return strlen(this->buff);
	}


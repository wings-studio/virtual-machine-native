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
	buff[ind + 1] = '\0';
	ind++;
}
l * StringBuilder::ToString() {
	return buff;
}
I Len() {
	return strlen(this->buff);
}
v StringBuilder::Clear() {
	ind = 0;
}
// @Depricated
v StringBuilder::Terminate() {
	buff[ind + 1] = '\0';
}
v StringBuilder::Remove(I b, I e){
    I end_s=strlen(buff);
    I pos=0;
    I pos_n=0;
    for (int i=b;i<e;i++)
       buff[i]='\0',
       pos++;
    for(int i=0;i<end_s;i++)
       if(buff[i]=='\0')
           continue;
       else
          buff_n[pos_n]=buff[i],
          pos_n++;
    int i;
    for ( i=0;i<pos_n;i++)
      buff[i]=buff_n[i];
    buff[i+1]='\0';
}
l* StringBuilder::Trim() {// удаляет пробелы | delete whitespaces
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

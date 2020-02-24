/* 
 * File:   SB.cpp
 * Author: papa
 *
 * Created on 22 февраля 2020 г., 15:01
 */
#include "utilMacr.h"
#include "SB.h"
#include <string>
#include <cstring>
StringBuilder::StringBuilder() {
	ind = 0;
}
v StringBuilder::Append(l char_) {
	buff[ind] = char_;
	buff[++ind] = '\0';
}
l * StringBuilder::ToString() {
	return buff;
}
S StringBuilder::ToStringCpp() {
	return  std::string(buff);
}
v StringBuilder::Clear() {
	ind = 0;
}
v StringBuilder::Terminate() {
	buff[ind + 1] = '\0';
}
v StringBuilder::Remove(I b, I e) {
	I s_len = strlen(buff);
	I pos = 0;
	for (int i = 0; i < s_len; i++)
		if (i >= b && i < e)
			continue;
		else
			buff_n[pos] = buff[i],
			pos++;
	buff_n[pos] = '\0';
	strcpy(buff, buff_n);
}
I StringBuilder::Len() {
	return strlen(this->buff);
}
l* StringBuilder::Trim() {// пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ | delete whitespaces
	I pos = 0;
	I s_len = strlen(buff);
	int i;
	for (i = 0; i < (s_len - 1); i++)
		if (buff[i] == ' ')
			continue;
		else
			buff_n[pos] =buff[i],
			pos++;
	buff_n[pos] = '\0';
	strcpy(buff, buff_n);
	return buff;
}

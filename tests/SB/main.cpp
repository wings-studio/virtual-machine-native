#include <stdlib.h>
#include <iostream>
#include "utilMacr.h"
#include <string.h>
#define buf_for_itlwm_keyword 10
class StringBuilder {
public :
	l buff[buf_for_itlwm_keyword];
	I ind;
	StringBuilder() {
		ind = 0;
	}
	v Append(cc char_) {
		buff[ind] = char_;
		ind++;
	}
	cc * ToString() {
		return buff;
	}
	v Clear() {
		ind = 0;
	}
	v Terminate(){
		buff[ind+1]='\0';
	}
	v Remove(I b,I e){
		for (int b = 0; b < e; b++);
			//buff[b]=''; // ошибка
	}
	cc * Trim(){// удаляет пробелы | delete whitespaces
		for (int i = 0; i < ind; i++)
			if(buff[i]==' ');
				//buff[i]=''; // ошибка
		return buff;
	}
};


/*
 * Simple C++ Test Suite
 */

//void StringBuilder::Append(char char_);

void testAppend() {
	char char_1='a';
	StringBuilder stringBuilder;
	stringBuilder.Append(char_1);
	
	char char_2='b';
//	StringBuilder stringBuilder;
	stringBuilder.Append(char_2);
	
	char char_3='c';
//	StringBuilder stringBuilder;
	stringBuilder.Append(char_3);
	
	stringBuilder.Terminate();
	cc* str=stringBuilder.ToString();
	if (strcmp(str,"abc") /*check result*/)
	{
		std::cout << "%TEST_FAILED% time=0 testname=testAppend (newsimpletest) message=error message sample" << std::endl;
	}
}

//void StringBuilder::Clear();

//void testClear() {
//	StringBuilder stringBuilder;
//	stringBuilder.Clear();
//	if (true /*check result*/)
//	{
//		std::cout << "%TEST_FAILED% time=0 testname=testClear (newsimpletest) message=error message sample" << std::endl;
//	}
//}

//void StringBuilder::Remove(int b, int e);

//void testRemove() {
//	int b;
//	int e;
//	StringBuilder stringBuilder;
//	stringBuilder.Remove(b, e);
//	if (true /*check result*/)
//	{
//		std::cout << "%TEST_FAILED% time=0 testname=testRemove (newsimpletest) message=error message sample" << std::endl;
//	}
//}

//StringBuilder::StringBuilder();

//void testStringBuilder() {
//	StringBuilder stringBuilder();
//	if (true /*check result*/)
//	{
//		std::cout << "%TEST_FAILED% time=0 testname=testStringBuilder (newsimpletest) message=error message sample" << std::endl;
//	}
//}

//void StringBuilder::Terminate();

void testTerminate() {
	StringBuilder stringBuilder;
	stringBuilder.Terminate();
	if (true /*check result*/)
	{
		std::cout << "%TEST_FAILED% time=0 testname=testTerminate (newsimpletest) message=error message sample" << std::endl;
	}
}

//char* StringBuilder::ToString();

void testToString() {
	StringBuilder stringBuilder;
	char* result = stringBuilder.ToString();
	if (true /*check result*/)
	{
		std::cout << "%TEST_FAILED% time=0 testname=testToString (newsimpletest) message=error message sample" << std::endl;
	}
}

//char* StringBuilder::Trim();

//void testTrim() {
//	StringBuilder stringBuilder;
//	char* result = stringBuilder.Trim();
//	if (true /*check result*/)
//	{
//		std::cout << "%TEST_FAILED% time=0 testname=testTrim (newsimpletest) message=error message sample" << std::endl;
//	}
//}

int main(int argc, char** argv) {
	std::cout << "%SUITE_STARTING% newsimpletest" << std::endl;
	std::cout << "%SUITE_STARTED%" << std::endl;

	std::cout << "%TEST_STARTED% testAppend (newsimpletest)" << std::endl;
	testAppend();
	std::cout << "%TEST_FINISHED% time=0 testAppend (newsimpletest)" << std::endl;

//	std::cout << "%TEST_STARTED% testClear (newsimpletest)" << std::endl;
//	testClear();
//	std::cout << "%TEST_FINISHED% time=0 testClear (newsimpletest)" << std::endl;

//	std::cout << "%TEST_STARTED% testRemove (newsimpletest)" << std::endl;
//	testRemove();
//	std::cout << "%TEST_FINISHED% time=0 testRemove (newsimpletest)" << std::endl;

//	std::cout << "%TEST_STARTED% testStringBuilder (newsimpletest)" << std::endl;
//	testStringBuilder();
//	std::cout << "%TEST_FINISHED% time=0 testStringBuilder (newsimpletest)" << std::endl;

//	std::cout << "%TEST_STARTED% testTerminate (newsimpletest)" << std::endl;
//	testTerminate();
//	std::cout << "%TEST_FINISHED% time=0 testTerminate (newsimpletest)" << std::endl;

//	std::cout << "%TEST_STARTED% testToString (newsimpletest)" << std::endl;
//	testToString();
//	std::cout << "%TEST_FINISHED% time=0 testToString (newsimpletest)" << std::endl;

//	std::cout << "%TEST_STARTED% testTrim (newsimpletest)" << std::endl;
//	testTrim();
//	std::cout << "%TEST_FINISHED% time=0 testTrim (newsimpletest)" << std::endl;

	std::cout << "%SUITE_FINISHED% time=0" << std::endl;

	return(EXIT_SUCCESS);
}


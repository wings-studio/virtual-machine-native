#include <stdlib.h>
#include <iostream>
#include "utilMacr.h"
#include "SB.h"
#include <string.h>

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

v StringBuilder::Clear() {
	ind = 0;
}

v StringBuilder::Terminate() {
	buff[ind + 1] = '\0';
}

l* StringBuilder::Remove(I b, I e) {
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
	printf("buff  in Trim beg %s\n", buff);
	I pos = 0;
	I s_len = strlen(buff);
	int i;
	for (i = 0; i < (s_len - 1); i++)
		if (buff[i] == ' ')
			continue;
		else
			buff_n[pos] =buff[i],
			pos++,
			printf("char %c\n",buff[i]), printf("pos %d\n",pos);
		
	buff_n[pos] = '\0';
	strcpy(buff, buff_n);
}


/*
 * Simple C++ Test Suite
 */

//void StringBuilder::Append(char char_);

void testAppend() {
	char char_1 = 'a';
	StringBuilder stringBuilder;
	stringBuilder.Append(char_1);

	char char_2 = 'b';
	//	StringBuilder stringBuilder;
	stringBuilder.Append(char_2);

	char char_3 = 'c';
	stringBuilder.Append(char_3);

	l* str = stringBuilder.ToString();
	if (strcmp(str, "abc") /*check result*/)
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

void testRemove() {
	StringBuilder stringBuilder;
	char char_01 = '{';
	stringBuilder.Append(char_01);
	char char_02 = ' ';
	stringBuilder.Append(char_02);
	char char_03 = ' ';
	stringBuilder.Append(char_03);
	char char_04 = ' ';
	stringBuilder.Append(char_04);

	char char_1 = 'w';

	stringBuilder.Append(char_1);

	char char_2 = 'o';
	stringBuilder.Append(char_2);

	char char_3 = 'l';
	stringBuilder.Append(char_3);
	char char_4 = 'v';
	stringBuilder.Append(char_4);
	char char_5 = 'm';
	stringBuilder.Append(char_5);
	stringBuilder.Remove(0, 1);
	//	printf("%s\n",stringBuilder.ToString());
	if (strcmp(stringBuilder.ToString(), "   wolvm"));
	{
		std::cout << "%TEST_FAILED% time=0 testname=testRemove (newsimpletest) message=error message sample" << std::endl;
	}
}

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

void testTrim() {
	StringBuilder stringBuilder;
	char char_01 = ' ';
	char char_02 = ' ';
	char char_03 = ' ';
	stringBuilder.Append(char_01);
	stringBuilder.Append(char_02);
	stringBuilder.Append(char_03);
	char char_1 = 'a';

	stringBuilder.Append(char_1);

	char char_2 = 'b';
	//	StringBuilder stringBuilder;
	stringBuilder.Append(char_2);

	char char_3 = 'c';
	//	StringBuilder stringBuilder;
	stringBuilder.Append(char_3);

	stringBuilder.Append(char_01);
	stringBuilder.Append(char_02);
	stringBuilder.Append(char_03);


	char* result = stringBuilder.Trim();
	printf("%s\n", result);

	if (strcmp(stringBuilder.ToString(), "abc"))
	{
		std::cout << "%TEST_FAILED% time=0 testname=testTrim (newsimpletest) message=error message sample" << std::endl;
	}
}

//int main(int argc, char** argv) {
//	std::cout << "%SUITE_STARTING% newsimpletest" << std::endl;
//	std::cout << "%SUITE_STARTED%" << std::endl;
//
//	std::cout << "%TEST_STARTED% testAppend (newsimpletest)" << std::endl;
//	testAppend();
//	std::cout << "%TEST_FINISHED% time=0 testAppend (newsimpletest)" << std::endl;
//
//	//	std::cout << "%TEST_STARTED% testClear (newsimpletest)" << std::endl;
//	//	testClear();
//	//	std::cout << "%TEST_FINISHED% time=0 testClear (newsimpletest)" << std::endl;
//
//		std::cout << "%TEST_STARTED% testRemove (newsimpletest)" << std::endl;
//		testRemove();
//	//	std::cout << "%TEST_FINISHED% time=0 testRemove (newsimpletest)" << std::endl;
//
//	//	std::cout << "%TEST_STARTED% testStringBuilder (newsimpletest)" << std::endl;
//	//	testStringBuilder();
//	//	std::cout << "%TEST_FINISHED% time=0 testStringBuilder (newsimpletest)" << std::endl;
//
////	std::cout << "%TEST_STARTED% testTerminate (newsimpletest)" << std::endl;
////	testTerminate();
//	//	std::cout << "%TEST_FINISHED% time=0 testTerminate (newsimpletest)" << std::endl;
//
//	//	std::cout << "%TEST_STARTED% testToString (newsimpletest)" << std::endl;
//	//	testToString();
//	//	std::cout << "%TEST_FINISHED% time=0 testToString (newsimpletest)" << std::endl;
//
//	std::cout << "%TEST_STARTED% testTrim (newsimpletest)" << std::endl;
//	testTrim();
//	//	std::cout << "%TEST_FINISHED% time=0 testTrim (newsimpletest)" << std::endl;
//
//	std::cout << "%SUITE_FINISHED% time=0" << std::endl;
//
//	return(EXIT_SUCCESS);
//}



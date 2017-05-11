#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include <string.h>
#include "qh_string.h"

void test1(){
	const char* ini_text = "just a test";
	qh::string a;
	assert(a.size() == 0);
	assert(a.data() == NULL);
	assert(a.c_str() == NULL);
	qh::string b(ini_text);
	assert(b.size() == strlen(ini_text));
	assert(strlen(b.c_str()) == strlen(ini_text));
	assert(strncmp(b.data(), ini_text, b.size()) == 0);
	for(int i = 0; i < b.size(); ++i){
		assert(ini_text[i] == b[i]);
	}
	a = b;
	assert(strncmp(a.c_str(), ini_text, strlen(ini_text)) == 0);
}

void test2(){
	const char* ini_text = "just a test";
	qh::string a(ini_text);
	qh::string b(ini_text, 4);
	assert(strncmp(b.data(), ini_text, 4) == 0);
	qh::string c(a);
	assert(strcmp(c.c_str(), ini_text) == 0);
	qh::string d = b;
	assert(strncmp(d.data(), ini_text, 4) == 0);
}

int main(int argc, char* argv[])
{
	test1();
	test2();
	printf("All success! Congratulations ~\n");

#ifdef WIN32
    system("pause");
#endif

	return 0;
}


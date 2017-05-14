#include "ini_parser.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

void test1()
{
    const char* ini_text= "a=1\nb=2\n"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "\n", "=")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "");
}

void test2()
{
    const char* ini_text= "a=1||b=2||c=3"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", "=")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "3");
}

void test3()
{
    const char* ini_text= "||||a:1||b:2||||c:3||||||"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", ":")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "3");
}

void test4()
{
	const std::string ini_path = "ini_text/unittest.ini";
	qh::INIParser parser;
	if(!parser.Parse(ini_path)){
		assert(false);
	}

	const std::string& a = parser.Get("section1", "a", NULL);
	assert(a == "3");

	const std::string& b = parser.Get("section1", "b", NULL);
	assert(b == "2");

	const std::string& c = parser.Get("section1", "c", NULL);
	assert(c == "1");

	const std::string& d = parser.Get("section1", "d", NULL);
	assert(d == "");

	const std::string& a1 = parser.Get("section2", "a", NULL);
	assert(a1 == "6");
	
	const std::string& b1 = parser.Get("section2", "b", NULL);
	assert(b1 == "5");

	const std::string& d1 = parser.Get("section3", "d", NULL);
	assert(d1 == "");

	const std::string& year = parser.Get("date", "year", NULL);
	assert(year == "2017");

	const std::string& month = parser.Get("date", "month", NULL);
	assert(month == "5");

	const std::string& hour = parser.Get("date", "hour", NULL);
	assert(hour == "11");

	const std::string& minute = parser.Get("date", "minute", NULL);
	assert(minute == "");
}

int main(int argc, char* argv[])
{
    test1();
    test2();
    test3();
	test4();

	printf("All test success!Congratulations~\n");

    return 0;
}



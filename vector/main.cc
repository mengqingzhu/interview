#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "qh_vector.h"

#define TEST_LENGTH 5

void test1(){
	const int ini_test[TEST_LENGTH] = {0, 1, 2, 3, 4};
	qh::vector<int> iVec;
	assert(iVec.size() == 0 && iVec.capacity() == 0 && iVec.empty());
	iVec.reserve(TEST_LENGTH - 1);
	assert(iVec.size() == 0 && iVec.capacity() == TEST_LENGTH - 1);
	for(int i = 0; i < TEST_LENGTH; ++i){
		iVec.push_back(ini_test[i]);
		assert(iVec[i] == ini_test[i]);
	}
	assert(iVec.size() == TEST_LENGTH && iVec.capacity() == 2 * (TEST_LENGTH - 1));
	qh::vector<int> iVec2(TEST_LENGTH,6);
	iVec = iVec2;
	assert(iVec.size() == TEST_LENGTH && iVec.capacity() == TEST_LENGTH);
	for(int i = 0; i < TEST_LENGTH; ++i){
		assert(iVec[i] == 6);
	}

	iVec.push_back(6);
	assert(iVec.size() == TEST_LENGTH + 1 && iVec.capacity() == 2 * TEST_LENGTH);
	iVec.pop_back();
	iVec.pop_back();
	assert(iVec.size() == TEST_LENGTH - 1 && iVec.capacity() == 2 * TEST_LENGTH);

	iVec.resize(TEST_LENGTH + 3, 8);
	assert(iVec[TEST_LENGTH] == 8 && iVec.size() == TEST_LENGTH + 3 && iVec.capacity() == 2 * TEST_LENGTH);
	iVec.resize(3 * TEST_LENGTH);
	assert(iVec.size() == 3 * TEST_LENGTH && iVec.capacity() == 3 * TEST_LENGTH);
	iVec.resize(TEST_LENGTH);
	assert(iVec.size() == TEST_LENGTH && iVec.capacity() == 3 * TEST_LENGTH);

	iVec.reserve(TEST_LENGTH);
	assert(iVec.capacity() == 3 * TEST_LENGTH);

	iVec.clear();
	assert(iVec.capacity() == 3 * TEST_LENGTH && iVec.empty());

}

void test2(){
	qh::vector<char *> sVec(TEST_LENGTH, NULL);
	qh::vector<char> cVec(TEST_LENGTH, 'a');
	qh::vector<int> iVec(TEST_LENGTH);
}

int main(int argc, char* argv[])
{
    test1();
	test2();

	printf("All test success!Congratulations ~\n");

#ifdef WIN32
    system("pause");
#endif

	return 0;
}


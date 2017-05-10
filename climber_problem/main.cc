#include <stdio.h>
#include <assert.h>

#define H_ARRAYSIZE(a) \
    ((sizeof(a) / sizeof(*(a))) / \
    static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

int getNum(int &num, const char * str){
	const char * pCurrent = str;
	num = 0;
	while(true){
		int temp = *pCurrent - '0';
		if(temp < 0 || temp > 9) break;
		num *= 10;
		num += temp;
		++pCurrent;
	}
	return pCurrent - str;
}

int getMountain(int &start, int &end, int &height, const char * str){
	const char * pCurrent = str;
	pCurrent += getNum(start, pCurrent);
	++pCurrent;
	pCurrent += getNum(end, pCurrent);
	++pCurrent;
	pCurrent += getNum(height, pCurrent);
	return pCurrent - str;
}

int resolve(const char* input)
{
	const char * pCurrent = input;
	int count;
	pCurrent += getNum(count, pCurrent);
	if(*pCurrent == '\n') ++pCurrent;
	if(count == 0) return 0;
	int mountains[count][3];
	int end = 0;
	for(int i = 0; i < count; ++i){
		pCurrent += getMountain(mountains[i][0], mountains[i][1], mountains[i][2], pCurrent);
		++pCurrent;
		end = mountains[i][1] >= end ? mountains[i][1] : end;
	}
	int dp[end];
	for(int i = 0; i < end; ++i){
		dp[i] = 0;
	}
	for(int i = 0; i < count; ++i){
		int height = mountains[i][2];
		for(int j = mountains[i][0]; j < mountains[i][1];++j){
			dp[j] = dp[j] >= height ? dp[j] : height;
		}
	}
	int result = 0;
	int before = 0;
	for(int i = 0; i < end; ++i){
		if(dp[i] > before){
			result += dp[i] - before + 1;
		}else{
			result += before - dp[i] + 1;
		}
		before = dp[i];
	}
	result += dp[end - 1];
    return result;
}

int main(int argc, char* argv[]) 
{
    const char* input[] = {
        "3\n1,3,2\n2,4,4\n6,7,5\n", //The giving example
        "1\n1,2,1\n",
        "2\n1,2,1\n2,3,2",
        "3\n1,2,1\n2,3,2\n3,6,1",
        "4\n1,2,1\n2,3,2\n3,6,1\n5,8,2",
        "5\n1,2,1\n2,3,2\n3,6,1\n5,8,2\n7,9,1",
        "1\n0,1,1",
        "2\n0,1,1\n2,4,3",
        "3\n0,1,1\n2,4,3\n3,5,1",
        "4\n0,1,1\n2,4,3\n3,5,1\n5,6,1",
        "5\n0,1,1\n2,4,3\n3,5,1\n5,6,1\n6,8,3",
		"5\n2,3,2\n3,6,1\n1,2,1\n7,9,1\n5,8,2",
		"2\n0,12,15\n2,11,19"
        };
    int expectedSteps[] = {25, 4, 7, 10, 14, 15, 3, 12, 13, 14, 20, 15, 50};
    for (size_t i = 0; i < H_ARRAYSIZE(input); ++i)
    {
        assert(resolve(input[i]) == expectedSteps[i]);
    }
    return 0;
}

#ifndef _COMPARE_RESULT_
#define _COMPARE_RESULT_

#include <string>

using namespace std;

class CompareResult{
public:
	CompareResult();

	CompareResult(int m, bool i, string a);

	int module;
	bool initial;
	string result;

	bool haveResult();
};

#endif
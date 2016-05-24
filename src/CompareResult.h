#ifndef _COMPARE_RESULT_
#define _COMPARE_RESULT_

#include <string>

using namespace std;

class CompareResult{
public:
	CompareResult(string a, string b, bool forceMerge);

	CompareResult(int m, bool i, string a);
	
	CompareResult();

	int module;
	bool initial;
	string result;

	bool haveResult();

	static int calcularInitialTrue(string s, string t);

	static int calcularInitialFalse(string s, string t);

	void calcularCompareResult(string x, string y, bool forceMerge);

	void calcResult(bool force);
};

#endif
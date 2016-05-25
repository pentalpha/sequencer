#ifndef _COMPARE_RESULT_
#define _COMPARE_RESULT_

#include <string>

using namespace std;

class StringMerge{
public:
	int module;
	bool initial;
	string result;

	StringMerge(string a, string b, bool forceMerge);
	StringMerge(int m, bool i, string a);
	StringMerge();

	bool haveResult();
	void compare(string x, string y, bool forceMerge);

protected:
	static int calcularInitialTrue(string s, string t);
	static int calcularInitialFalse(string s, string t);
	void calcModule(string first, string second);
};

#endif
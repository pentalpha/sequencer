#ifndef _COMPARE_RESULT_
#define _COMPARE_RESULT_

#include <string>

using namespace std;

/**
	@brief	Handles the combination of a pair of strings
	
	@author Pitágoras Alves
	@date	May 2016
*/
class StringMerge{
public:
	int module;
	bool initial;
	string result;
	
	
	StringMerge(string a, string b, bool forceMerge);
	StringMerge(int m, bool i, string a);
	StringMerge();
	bool haveResult();

protected:
	
	void compare(string x, string y, bool forceMerge);
	static int calcularInitialTrue(string s, string t);
	static int calcularInitialFalse(string s, string t);
	void calcModule(string first, string second);
};

#endif
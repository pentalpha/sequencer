#ifndef _STRING_PAIR_
#define _STRING_PAIR_
#include <string>
#include <omp.h>

#define FIRST 0
#define LAST  size()-1

using namespace std;

struct CompareResult{
	CompareResult();

	CompareResult(int m, bool i, string a);

	int module;
	bool initial;
	string result;

	bool haveResult();
};

class StringPair{
public:
	string x;
	string y;
	bool compared;
	CompareResult result;

	StringPair();

	StringPair(string a, string b);

	string mergePair(StringPair a, int module, bool initial);

	string printPair();

	int calcularInitialTrue(string s, string t);

	int calcularInitialFalse(string s, string t);

	void calcularCompareResult(bool forceMerge = false);

	void calcResult(bool force);
};

inline bool operator==(const StringPair& first, const StringPair& second){
	if((first.x.compare(second.x) == 0) && (first.y.compare(second.y) == 0)){
		return true;
	}else if((first.x.compare(second.y) == 0) && (first.y.compare(second.x) == 0)){
		return true;
	}
	return false;
}

inline bool operator!=(const StringPair& first, const StringPair& second){
	return (!(first == second));
}

#endif
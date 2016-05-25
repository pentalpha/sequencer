#ifndef _STRING_PAIR_
#define _STRING_PAIR_
#include <string>
#include <omp.h>
#include "StringMerge.h"

#define FIRST 0
#define LAST  size()-1

using namespace std;

class StringPair{
public:
	string x;
	string y;

	StringPair();

	StringPair(string a, string b);

	static string mergePair(StringPair a, int module, bool initial);

	string printPair();
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

inline bool operator<(const StringPair& first, const StringPair& second){
	return ((first.x.length() + first.y.length()) < (second.x.length() + second.y.length()));
}

inline bool operator>(const StringPair& first, const StringPair& second){
	return ((first.x.length() + first.y.length()) > (second.x.length() + second.y.length()));
}

inline bool operator>=(const StringPair& first, const StringPair& second){
	return (first > second || first == second);
}

inline bool operator<=(const StringPair& first, const StringPair& second){
	return (first < second || first == second);
}

#endif
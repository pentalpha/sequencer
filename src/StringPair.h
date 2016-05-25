#ifndef _STRING_PAIR_
#define _STRING_PAIR_
#include <string>
#include <omp.h>
#include "StringMerge.h"

#define FIRST 0
#define LAST  size()-1

using namespace std;

/**
	@brief	Pair of strings, the order of the strings does not matter.
	@author Pitágoras Alves
	@date	May 2016
*/
class StringPair{
public:
	string x;
	string y;

	StringPair();

	StringPair(string a, string b);
	/**
		Merge two strings according to a certain magnitude and a direction.
		@param	a	Pair of strings to merge.
		@param	module	Module of the merge, lenght of characters equals in both strings.
		@param	initial	If the first string will be merged in the beggining of the second, false if the contrary.
		
		@return The merged string
	*/
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
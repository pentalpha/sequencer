#ifndef _STRING_PAIR_
#define _STRING_PAIR_
#include <string>

using namespace std;

struct CompareResult{
	CompareResult(){
		module = -1;
		initial = false;
	}
	CompareResult(int m, bool i){
		module = m;
		initial = i;
	}
	int module;
	bool initial;
	string result;
};

class StringPair{
public:
	string x;
	string y;
	bool compared;
	CompareResult result;
	StringPair(){
		x = "";
		y = "";
		compared = false;
	}
	StringPair(string a, string b){
		x = a;
		y = b;
		compared = false;
	}

	string printPair(){
		return x + ", " + y;
	}

	void calcResult(){
			if(!compared){
					//result = calcularCompareResult(StringPair(this->x, this->y));
					compared = true;
			}
	}
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

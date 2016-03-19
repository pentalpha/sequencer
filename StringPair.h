#ifndef _STRING_PAIR_
#define _STRING_PAIR_
#include <string>

using namespace std;

struct StringPair{
	StringPair(string a, string b){
		x = a;
		y = b;
	}
	string x;
	string y;
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

	struct CompareResult{
		CompareResult(int m, bool i){
			module = m;
			initial = i;
		}
		int module;
		bool initial;
	};

string mergePair(StringPair a, CompareResult comp){
	string result;
	string cuttedY;
	if(comp.initial){
		cuttedY = a.y.substr(0, a.y.size() - comp.module);
		result = cuttedY;
		result.append(a.x);
	}else{
		cuttedY =  a.y.substr(comp.module,  a.y.size() - comp.module);
		result = a.x;
		result.append(cuttedY);
	}

	return result;
}


#endif

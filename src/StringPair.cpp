#include <string>
#include <omp.h>
#include "StringPair.h"

using namespace std;

StringPair::StringPair(){
	x = "";
	y = "";
}

StringPair::StringPair(string a, string b){
	x = a;
	y = b;
}

string StringPair::mergePair(StringPair a, int module, bool initial){
	string result;
	string cuttedY;
	if(initial){
		cuttedY = a.y.substr(0, a.y.size() - module);
		result = cuttedY;
		result.append(a.x);
	}else{
		cuttedY =  a.y.substr(module,  a.y.size() - module);
		result = a.x;
		result.append(cuttedY);
	}

	return result;
}

string StringPair::printPair(){
	return x + ", " + y;
}
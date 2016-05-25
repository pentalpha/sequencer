#include <string>
#include <omp.h>
#include <assert.h>
#include "StringPair.h"

using namespace std;

StringPair::StringPair(){
	x = "";
	y = "";
}

StringPair::StringPair(string a, string b){
	assert(a.size() >= 1 && b.size() >= 1);
	
	x = a;
	y = b;
}

string StringPair::mergePair(StringPair a, int module, bool initial){
	assert(module >= 0);
	assert(a.x.size() >= 1 && a.y.size() >= 1);
	
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
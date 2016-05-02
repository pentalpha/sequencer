#include <string>
#include "CompareResult.h"

using namespace std;

CompareResult::CompareResult(){
	module = -1;
	initial = false;
}

CompareResult::CompareResult(int m, bool i, string a){
	module = m;
	initial = i;
	result = a;
}

bool CompareResult::haveResult(){
	return (result != "");
}
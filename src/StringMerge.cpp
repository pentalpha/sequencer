#include <string>
#include <assert.h>
#include "StringPair.h"
#include "StringMerge.h"

using namespace std;

StringMerge::StringMerge(string a, string b, bool forceMerge){
	assert(a.length() > 0);
	assert(b.length() > 0);
	
	module = -1;
	initial = false;
	compare(a, b, forceMerge);
}

StringMerge::StringMerge(int m, bool i, string a){
	assert(a.length() > 0);
	
	module = m;
	initial = i;
	result = a;
}

StringMerge::StringMerge(){
	
}

bool StringMerge::haveResult(){
	return (result != "");
}

int StringMerge::calcularInitialTrue(string s, string t){
	assert(s.length() > 0);
	assert(t.length() > 0);
	
	int length = 0;

	string busca;
	for(int i = 0; i < t.size(); i++){
		busca = t.substr(t.size()-1-i);
		if(s.substr(0,i+1) == busca){
			length = busca.size();
		}
	}
	return length;
}

void StringMerge::calcModule(string first, string second){
	assert(first.length() > 0);
	assert(second.length() > 0);
	
	int initialTrue;
	int initialFalse;

	initialTrue = calcularInitialTrue(first,second);
	initialFalse = calcularInitialTrue(second,first);

	if(initialTrue >= initialFalse){
		module  = initialTrue;
		initial = true;
	} else {
		module  = initialFalse;
		initial = false;
	}
}

void StringMerge::compare(string first, string second, bool forceMerge){
	assert(first.length() > 0);
	assert(second.length() > 0);
	
	int minModule = (int)((first.size()+second.size())/2 * 0.05);
	if(minModule <= 0){ minModule = 1;}

	calcModule(first, second);

	if(module < minModule && !forceMerge){
		result = "";
	}else{
		result = StringPair::mergePair(StringPair(first, second), module, initial);
	}
}
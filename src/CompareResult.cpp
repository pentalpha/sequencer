#include <string>
#include "StringPair.h"
#include "CompareResult.h"

using namespace std;

CompareResult::CompareResult(string a, string b, bool forceMerge){
	module = -1;
	initial = false;
	calcularCompareResult(a, b, forceMerge);
}

CompareResult::CompareResult(int m, bool i, string a){
	module = m;
	initial = i;
	result = a;
}

CompareResult::CompareResult(){
	
}

bool CompareResult::haveResult(){
	return (result != "");
}

int CompareResult::calcularInitialTrue(string s, string t){
	int length = 0;

	string busca;
	for(int i = 0; i < t.size(); i++){
		busca = t.substr(t.size()-1-i);

		// cout << "T Compara " << busca << " com " << s.substr(0,i+1) << " ";

		if(s.substr(0,i+1) == busca){
			length = busca.size();
			// cout << "length++";
		}
		// cout << "\n";
	}
	return length;
}

int CompareResult::calcularInitialFalse(string s, string t){
	int length = 0;

	string busca;
	for(int i = 0; i < s.size(); i++){
		busca = s.substr(s.size()-1-i);

		// cout << "F Compara " << busca << " com " << t.substr(0,i+1) << " ";

		if(t.substr(0,i+1) == busca){
			// cout << "length++";
			length = busca.size();
		}
		// cout << "\n";
	}

	return length;
}

void CompareResult::calcularCompareResult(string x, string y, bool forceMerge){

	//CompareResult comp(0,false,"");

	string first  = x;
	string second = y;
	int minModule = (int)((first.size()+second.size())/2 * 0.05);
	if(minModule <= 0){ minModule = 1;}

	int initialTrue;
	int initialFalse;

	initialTrue = calcularInitialTrue(first,second);
	initialFalse = calcularInitialFalse(first,second);

	if(initialTrue >= initialFalse){
		module  = initialTrue;
		initial = true;
	} else {
		module  = initialFalse;
		initial = false;
	}

	result = (module < minModule && !forceMerge) ? "" : StringPair::mergePair(StringPair(first, second), module, initial);
}
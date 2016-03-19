#ifndef __COMPARERESULTCALCULATOR__
#define __COMPARERESULTCALCULATOR__

#include "StringPair.h"

#define FIRST 0
#define LAST  size()-1

using namespace std;

string mergePair(StringPair a, int module, bool initial){
	cout << module << " " << initial << "\n";

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

int calcularInitialTrue(string s, string t){
	int length = 0;

	string busca;
	for(int i = 0; i < t.size(); i++){
		busca = t.substr(t.size()-1-i);

		cout << "T Compara " << busca << " com " << s.substr(0,i+1) << " ";

		if(s.substr(0,i+1) == busca){
			length = busca.size();
			cout << "length++";
		}
		cout << "\n";
	}
	return length;
}

int calcularInitialFalse(string s, string t){
	int length = 0;

	string busca;
	for(int i = 0; i < s.size(); i++){
		busca = s.substr(s.size()-1-i);

		cout << "F Compara " << busca << " com " << t.substr(0,i+1) << " ";

		if(t.substr(0,i+1) == busca){
			cout << "length++";
			length = busca.size();
		}
		cout << "\n";
	}

	return length;
}

CompareResult calcularCompareResult(StringPair pairOfStrings){
	CompareResult comp(0,false,"");

	string first  = pairOfStrings.x;
	string second = pairOfStrings.y;

	int initialTrue = calcularInitialTrue(first,second);
	int initialFalse = calcularInitialFalse(first,second);

	if(initialTrue >= initialFalse){
		comp.module  = initialTrue;
		comp.initial = true;
	} else {
		comp.module  = initialFalse;
		comp.initial = false;
	}

	comp.result = mergePair(pairOfStrings,comp.module,comp.initial);

	return comp;
}

#endif

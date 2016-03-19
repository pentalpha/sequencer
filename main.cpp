#include <iostream>
#include "StringPair.h"

using namespace std;

int main(int argc, char **argv){
	StringPair a("abc", "bcd");
	StringPair b("bcd", "abc");

	if(a != b){
		cout << "A and B are unequal\n";
	}

	if(a == b){
		cout << "A and B are equal\n";
	}

	return 0;
}

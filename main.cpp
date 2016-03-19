#include <iostream>
#include "CompareResultCalculator.h"

using namespace std;

int main(int argc, char **argv){
	StringPair a("abcde", "defgh");
	StringPair b("defgh", "abcde");

	CompareResult res1(2, false), res2(2, true);
	cout << mergePair(a, res1) << "\n" << mergePair(b, res2) << "\n";


	return 0;
}

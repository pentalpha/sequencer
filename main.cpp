#include <iostream>
#include <string>
#include "StringPair.h"
#include "CompareResultCalculator.h"

using namespace std;

int main(int argc, char **argv){
	/*StringPair a("abcde", "defgh");
	StringPair b("defgh", "abcde");

	CompareResult res1(2, false), res2(2, true);
	cout << mergePair(a, res1) << "\n" << mergePair(b, res2) << "\n";*/

	//TO TO: entrada de dados. Entrada provisoria:
	int nSegments = 4;
	string segments[nSegments] = {"abc", "cde", "efg", "ghij"};

	//matriz com cada um dos segmentos comparado com os outros
	//a matriz não possui os elementos que estão na diagonal
	//nem os elementos acima da diagonal
	//(por motivos de economia de memoria)
	StringPair** matrix = new StringPair*[nSegments];
	for(int i = 0; i < nSegments; i++){
		int length = i;
		matrix[i] = new StringPair[length];
		cout << "line " << i << " has " << length << " comparisons\n";
	}

	//inicialização de cada comparação
	//ATENÇÃO: A iteração sobre a matriz deve obedecer este formato abaixo
	//	 			 ou vão ocorrer falhas de segmentação
	int n = 0;
	for(int i = 1; i < nSegments; i++){
		for(int j = 0; j < i; j++){
			matrix[i][j] = StringPair(segments[i],segments[j]);
			//matrix[i][j].calcResult();
			n++;
		}
	}
	cout << n << " different pairs on the matrix\n";


	return 0;
}

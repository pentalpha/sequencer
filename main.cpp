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
	int oldNSegments;
	int nSegments = 4;
	string segments[nSegments] = {"abc", "cde", "efg", "ghij"}, oldSegments*;

	//matriz com cada um dos segmentos comparado com os outros
	//a matriz não possui os elementos que estão na diagonal
	//nem os elementos acima da diagonal
	//(por motivos de economia de memoria)
	StringPair** oldMatrix = null;
	StringPair** matrix;

	while(nSegments > 1){
		matrix = new StringPair*[nSegments];
		for(int i = 0; i < nSegments; i++){
			int length = i;
			matrix[i] = new StringPair[length];
			cout << "line " << i << " has " << length << " comparisons\n";
		}

		//inicialização de cada comparação
		//ATENÇÃO: A iteração sobre a matriz deve obedecer este formato abaixo
		//	 			 ou vão ocorrer falhas de segmentação
		int n = 0;
		int xMax = 1, yMax = 0;
		for(int i = 1; i < nSegments; i++){
			for(int j = 0; j < i; j++){
				matrix[i][j] = StringPair(segments[i],segments[j]);
				matrix[i][j].calcResult();
				if(matrix[i][j].result.module > 0){
					cout << "Merging -" << segments[i] << "- with -" << segments[j] << "- results in ->\n" << matrix[i][j].result.result <<"\n";
				}
				if(matrix[i][j].result.module > matrix[xMax][yMax].result.module){
					xMax = i;
					yMax = j;
				}
				n++;
			}
		}

		//yMax sempre vem antes de xMax, a matriz garante isso!
		StringPair bestMerge = matrix[xMax][yMax];
		cout << "--------------------\nThe best merge in the iteration is:\n ";
		cout << "Merging -" << segments[xMax] << "- with -" << segments[yMax] << "- results in ->\n" << bestMerge.result <<"\n";

		String* newSegments = new newSegments[nSegments-1];
		for(int i = 0; i < yMax; i++){
			newSegments[i] = segments[i];
		}
		newSegments[yMax] = bestMerge.result;

		for(int i = yMax+1; i < xMax; i++){
			newSegments[i] = segments[i];
		}
		for(int i = xMax+1; i < nSegments; i++){
			newSegments[i-1] = segments[i];
		}

		StringPair* oldSegments = segments;
		segments = newSegments;

		oldNSegments = nSegments;
		nSegments -= 1;

		oldMatrix = matrix;

		cout << n << " different pairs on the matrix\n";
	}
	cout << segments[0];



	return 0;
}

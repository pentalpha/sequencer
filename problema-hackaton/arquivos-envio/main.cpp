#include <iostream>
#include <string>
#include <cstdio>
#include "StringPair.h"

#ifdef _OPENMP
#include <omp.h>
#define TRUE  1
#define FALSE 0
#else
#define omp_get_thread_num() 0
#endif

using namespace std;

string first20char(string a){
	if(a.size() <= 17){
		return a;
	}
	return a.substr(0, 17) + "...";
}

string last20char(string a){
	if(a.size() <= 17){
		return a;
	}
	return  "..." + a.substr(a.size()-17, 17);
}

void copyStringVector(string* v1, string* v2, int size){
	for(int i = 0; i < size; i++){
		v2[i] = v1[i];
	}
}

int main(int argc, char **argv){
	/*StringPair a("abcde", "defgh");
	StringPair b("defgh", "abcde");

	CompareResult res1(2, false), res2(2, true);
	cout << mergePair(a, res1) << "\n" << mergePair(b, res2) << "\n";*/

	//TO TO: entrada de dados. Entrada provisoria:
	int oldNSegments;
	int nSegments = 0;
	int allocateSegments = 50;
	string* segments = new string[allocateSegments];
	string line;
	while(getline(cin, line)){
		if(nSegments >= allocateSegments){
			//cout << "alocando mais memoria para o vetor de entrada\n";
			string* auxVector = new string[allocateSegments];
			copyStringVector(segments, auxVector, nSegments);
			int newAllocatorSize = allocateSegments + allocateSegments;
			segments = new string[newAllocatorSize];
			copyStringVector(auxVector, segments, nSegments);
			allocateSegments = newAllocatorSize;
		}
		nSegments++;
		if(line[line.size()-1] == '\r'){

			line = line.substr(0, line.size()-1);
			//cout << "quebra de linha barra r retirada  \n";
		}
		segments[nSegments-1] = line;
	}

	if(nSegments < allocateSegments){
		//cout << "desalocando memoria desnecessaria no vetor de entrada\n";
		string* auxVector = new string[nSegments];
		copyStringVector(segments, auxVector, nSegments);
		segments = new string[nSegments];
		copyStringVector(auxVector, segments, nSegments);
	}
	for(int i = 0; i < nSegments; i++){
		//cout << "----------------------------\nSegmento "<< i << ":\n" << segments[i] << "\n";
	}
	if(segments[0][segments[0].size()-1] != '.'){
		//cout << "the last character in <full genome sequencing.> is not a point\n";
	}
	//segments[0] = "abc";
	//segments[1] = "cde";
	//segments[2] = "efg";
	//segments[3] = "ghij";
	string* oldSegments;
	int iteration = 1;
	//matriz com cada um dos segmentos comparado com os outros
	//a matriz não possui os elementos que estão na diagonal
	//nem os elementos acima da diagonal
	//(por motivos de economia de memoria)
	StringPair** oldMatrix = NULL;
	StringPair** matrix;

	while(nSegments > 1){

		#ifdef _OPENMP
		(void) omp_set_dynamic(FALSE);
		(void) omp_set_num_threads(nSegments);
		#endif

		//std::cout << "===============Iteration " << iteration << "=================\n";
		matrix = new StringPair*[nSegments];

		#pragma omp parallel
		{
			#pragma omp parallel for
			for(int length = 0; length < nSegments; length++){
				matrix[length] = new StringPair[length];
				// cout << "line " << i << " has " << length << " comparisons\n";
			}
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
					//cout << "Merging -" << segments[i] << "- with -" << segments[j] << "- results in ->\n" << matrix[i][j].result.result <<"\n";
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
		//cout << "segments " << yMax << " with " << xMax << ":\n";
		//cout << "--------------------\nThe best merge in the iteration is:\n ";
		//cout << "x = \"" << first20char(bestMerge.x) << " -> " << last20char(bestMerge.x) << "\"\n";
		// << "- with -" << segments[yMax] << "- results in ->\n" << bestMerge.result.result << "\n";
		//cout << "+\n";
		//cout << "y = \"" << first20char(bestMerge.y) << " -> " << last20char(bestMerge.y) << "\"\n";
		//cout << "(initial = " << bestMerge.result.initial << ")\n";
		//cout << "=\n";
		//cout << "(" << bestMerge.result.module << " em comum)\n";
		//cout << bestMerge.result.result << "\n";

		string* newSegments = new string[nSegments-1];

		#pragma omp parallel
		{
			#pragma omp for
			for(int i = 0; i < yMax; i++){
				newSegments[i] = segments[i];
			}
		}
		newSegments[yMax] = bestMerge.result.result;

		#pragma omp parallel
		{
			#pragma omp for
			for(int i = yMax+1; i < xMax; i++){
				newSegments[i] = segments[i];
			}
		}

		for(int i = xMax+1; i < nSegments; i++){
			newSegments[i-1] = segments[i];
		}

		oldSegments = segments;
		segments = newSegments;

		oldNSegments = nSegments;
		nSegments -= 1;

		oldMatrix = matrix;

		//cout << n << " different pairs on the matrix\n";
		//std::cout << "===============Iteration " << iteration << "=================\n\n";
		iteration++;
	}
	//cout << "\n----------------- Resultado: --------------------\n";
	//cout << segments[0].size() << " caracteres\n";
	cout << segments[0] << "\n";



	return 0;
}

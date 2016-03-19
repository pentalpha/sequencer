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

int main(int argc, char **argv){
	/*StringPair a("abcde", "defgh");
	StringPair b("defgh", "abcde");

	CompareResult res1(2, false), res2(2, true);
	// cout << mergePair(a, res1) << "\n" << mergePair(b, res2) << "\n";*/

	//TO TO: entrada de dados. Entrada provisoria:
	int oldNSegments;
	int nSegments = 5;
	string* segments = new string[nSegments];
	segments[0] = "fragmentation and sequencing. Computer programs then use the overlapping ends of different reads to assemble them into a continuous sequence. Shotgun sequencing was one of the precursor technologies that was responsible for enabling full genome sequencing.";
	segments[1] = "sequenced using the chain termination method to obtain reads. Multiple overlapping reads for the target DNA are obtained by performing several rounds of this fragmentation and sequencing. Computer programs then use the overlapping ends of different reads to assemble";
	segments[2] = "methods are used for this: primer walking (or \"chromosome walking\") which progresses through the entire strand piece by piece, and shotgun sequencing which is a faster but more complex process that uses random fragments. In shotgun sequencing, DNA is broken up randomly into numerous small segments, which are sequenced using the chain termination method to obtain reads. Multiple se";
	segments[3] = "quasi-random firing pattern of a shotgun. The chain termination method of DNA sequencing (or \"Sanger sequencing\" for its developer Frederick Sanger) can only be used for fairly short strands of 100 to 1000 base pairs. Longer sequences are subdivided into smaller fragments that can be sequenced separately, and subsequently they are re-assembled to give the overall sequence. Two principal methods are used for this: primer me";
	segments[4] = "In genetics, shotgun sequencing, also known as shotgun cloning, is a method used for sequencing long DNA strands. It is named by analogy with the rapidly expanding, quasi-random firing pattern of a shotgun. The chain termination method of DNA sequencing (or \"Sanger sequencing\" for its developer q";
	string* oldSegments;

	//matriz com cada um dos segmentos comparado com os outros
	//a matriz não possui os elementos que estão na diagonal
	//nem os elementos acima da diagonal
	//(por motivos de economia de memoria)
	StringPair** oldMatrix = NULL;
	StringPair** matrix;

	while(nSegments > 1){
		matrix = new StringPair*[nSegments];

		#pragma omp parallel num_threads(nSegments)
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
					// cout << "Merging -" << segments[i] << "- with -" << segments[j] << "- results in ->\n" << matrix[i][j].result.result <<"\n";
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
		// cout << "--------------------\nThe best merge in the iteration is:\n ";
		// cout << "Merging -" << segments[xMax] << "- with -" << segments[yMax] << "- results in ->\n" << bestMerge.result.result << "\n";

		string* newSegments = new string[nSegments-1];

		#pragma omp parallel
		{
			#pragma omp for
			for(int i = 0; i < yMax; i++){
				newSegments[i] = segments[i];
			}
		}
		
		newSegments[yMax] = bestMerge.result.result;

		for(int i = yMax+1; i < xMax; i++){
			newSegments[i] = segments[i];
		}

		for(int i = xMax+1; i < nSegments; i++){
			newSegments[i-1] = segments[i];
		}

		oldSegments = segments;
		segments = newSegments;

		oldNSegments = nSegments;
		nSegments -= 1;

		oldMatrix = matrix;


		// cout << n << " different pairs on the matrix\n";
	}
	cout << segments[0];



	return 0;
}

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include "StringPair.h"

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
	#pragma omp parallel
	{
		#pragma omp for
		for(int i = 0; i < size; i++){
			v2[i] = v1[i];
		}
	}
}

void processBucket(string* &segments, int &nSegments, bool forceMerge);

int main(int argc, char **argv){

	int segmentsPerBucket = 200;
	int totalSegments = 0;
	string line;
	vector<string> tempSegments;
	vector<vector<string> > tempBuckets;
	while(getline(cin, line)){
		if(line[line.size()-1] == '\r'){

			line = line.substr(0, line.size()-1);
			//// cout << "quebra de linha barra r retirada  \n";
		}
		tempSegments.push_back(line);
		totalSegments++;
		if(tempSegments.size() == segmentsPerBucket){
			tempBuckets.push_back(tempSegments);
			tempSegments.clear();
		}
	}
	if(!tempSegments.empty()){
		tempBuckets.push_back(tempSegments);
		tempSegments.clear();
	}
	int nBuckets = tempBuckets.size();
	int nSegmentsInBucket[nBuckets];
	string** buckets = new string*[nBuckets];
	for(int i = 0; i < nBuckets; i++){
		nSegmentsInBucket[i] = tempBuckets[i].size();
		buckets[i] = new string[nSegmentsInBucket[i]];
		for(int j = 0; j < nSegmentsInBucket[i]; j++){
			buckets[i][j] = tempBuckets[i][j];
		}
		tempBuckets[i].clear();
	}
	tempBuckets.clear();

	#pragma omp parallel
	{
		#pragma omp for
		for(int actualBucket = 0; actualBucket < nBuckets; actualBucket++){
		// cout << "Bucket " << actualBucket <<":\n";
		// cout << "the bucket " << actualBucket << " have " << nSegmentsInBucket[actualBucket] << "." << endl;
			processBucket(buckets[actualBucket], nSegmentsInBucket[actualBucket], false);
		//nSegmentsInBucket[actualBucket] = nSegments;
		// cout << "Final processing of the bucket[outside]\n";
		//for (int i = 0; i < nSegmentsInBucket[actualBucket]; i++){
			// cout << "segments[" << i << "] = \"" << buckets[actualBucket][i] << "\"\n";
		//}
		// cout << "the bucket " << actualBucket << " now have " << nSegmentsInBucket[actualBucket] << "." << endl;
		}
		
	}
	
	int segmentsLeft = 0;
	for(int i = 0; i < nBuckets; i++){
		segmentsLeft += nSegmentsInBucket[i];
	}
	// cout << segmentsLeft << " segments left in total." << endl;
	string* finalBucket = new string[segmentsLeft];
	int index = 0;
	for(int i = 0; i < nBuckets; i++){
		for(int j = 0; j < nSegmentsInBucket[i]; j++){
			finalBucket[index] = buckets[i][j];
			index++;
		}
	}
	// cout << "Bucket final:\n";
	processBucket(finalBucket, segmentsLeft, true);
	string textoSaida = finalBucket[0];
	//replace(textoSaida.begin(),textoSaida.end(),"%%","\n");

	for(int i = 0; i < textoSaida.size()-1; i++){
		if((textoSaida[i] == '%') && (textoSaida[i+1] == '%')){
			textoSaida.replace(i,2,"\n");
		}
	}


	cout << textoSaida;

	return 0;
}

void processBucket(string* &segments, int &nSegments, bool forceMerge){
	int oldNSegments;

	int mergeIndex = -1;
	int erasedIndex = -1;
	int* oldPositions = NULL;

	/*for(int i = 0; i < nSegments; i++){
		// cout << "----------------------------\nSegmento "<< i << ":\n" << segments[i] << "\n";
	}
	if(segments[0][segments[0].size()-1] != '.'){
		// cout << "the last character in <full genome sequencing.> is not a point\n";
	}*/
		string* oldSegments;
		int iteration = 1;
	//matriz com cada um dos segmentos comparado com os outros
	//a matriz não possui os elementos que estão na diagonal
	//nem os elementos acima da diagonal
	//(por motivos de economia de memoria)
		StringPair** oldMatrix = new StringPair*[nSegments];
		StringPair** matrix    = new StringPair*[nSegments];
		bool mergedSomething = false;
		while(nSegments > 1){

		#ifdef _OPENMP
			(void) omp_set_dynamic(0);
			(void) omp_set_num_threads(nSegments);
		#endif

		// cout << "===============Iteration " << iteration << "=================\n";
		//for (int i = 0; i < nSegments; i++){
			// cout << "segments[" << i << "] = \"" << first20char(segments[i]) << " -> " << last20char(segments[i]) << "\"\n";
		//}

		#pragma omp parallel
			{
			#pragma omp parallel for
				for(int length = 0; length < nSegments; length++){
					matrix[length]    = new StringPair[length];
					oldMatrix[length] = new StringPair[length];
				 //// cout << "line " << length << " has " << length << " comparisons\n";
				}
			}

		//inicialização de cada comparação
		//ATENÇÃO: A iteração sobre a matriz deve obedecer este formato abaixo
		//	 		ou vão ocorrer falhas de segmentação
			int n = 0;
			int xMax = 1, yMax = 0;

			for(int i = 1; i < nSegments; i++){
				for(int j = 0; j < i; j++){
				//utilizar dados da matriz antiga
					bool reciclado = false;

					if((iteration > 1)
						&& (mergeIndex != -1 && erasedIndex != -1)
						&& (oldPositions != NULL)
						&& (j != mergeIndex && i != mergeIndex)){
							// cout << "tentando reciclar " << i << " e " << j << " Passo 1" << endl;
						int oldI = oldPositions[i];
						int oldJ = oldPositions[j];
						if(j < i){
							// cout << "tentando reciclar os antigos " << oldI << " e " << oldJ << " Passo 2" << endl;
							matrix[i][j] = oldMatrix[oldI][oldJ];
							reciclado = true;
							// cout << "reciclado" << endl;
					}
				}
				if(!reciclado){
					matrix[i][j] = StringPair(segments[i],segments[j]);
					matrix[i][j].calcResult(forceMerge);
				}

				//if(matrix[i][j].result.module > 0){
					//// cout << "Merging -" << segments[i] << "- with -" << segments[j] << "- results in ->\n" << matrix[i][j].result.result <<"\n";
				//}
				if(matrix[i][j].result.module > matrix[xMax][yMax].result.module){
					xMax = i;
					yMax = j;
				}
				n++;
			}
		}



		//yMax sempre vem antes de xMax, a matriz garante isso!
		StringPair bestMerge = matrix[xMax][yMax];
		// cout << "segments " << yMax << " with " << xMax << ":\n";
		// cout << "--------------------\nThe best merge in the iteration is:\n ";
		// cout << "x = \"" << first20char(bestMerge.x) << " -> " << last20char(bestMerge.x) << "\"\n";
		// cout << "+\n";
		// cout << "y = \"" << first20char(bestMerge.y) << " -> " << last20char(bestMerge.y) << "\"\n";
		// cout << "(initial = " << bestMerge.result.initial << ")\n";
		// cout << "=\n";
		// cout << "(" << bestMerge.result.module << " em comum)\n";
		// cout << bestMerge.result.result << "\n";
		if(bestMerge.result.haveResult()){
			string* newSegments = new string[nSegments-1];
			oldPositions = new int[nSegments-1];
		
			for(int i = 0; i < yMax; i++){
				newSegments[i] = segments[i];
			}
			

			newSegments[yMax] = bestMerge.result.result;

			mergeIndex = yMax;
			erasedIndex  = xMax;

			for(int i = yMax+1; i < xMax; i++){
				newSegments[i] = segments[i];
			}
			

			for(int i = xMax+1; i < nSegments; i++){
				newSegments[i-1] = segments[i];
			}

			for(int i = 0; i < nSegments-1; i++){
				oldPositions[i] = i;
				if(i >= xMax){
					oldPositions[i]++;
				}
			}

			oldSegments = segments;
			segments = newSegments;

			oldNSegments = nSegments;
			nSegments -= 1;

			#pragma omp parallel
			{
				for(int i = 1; i < nSegments; i++){
					for(int j = 0; j < i; j++){
						oldMatrix[i][j] = matrix[i][j];
					}
				}
			}
		}else{
			break;
		}
		// cout << "===============Iteration " << iteration << "=================\n\n";
		iteration++;
	}
	// cout << "Final processing of the bucket[inside]\n";
	//for (int i = 0; i < nSegments; i++){
		// cout << "segments[" << i << "] = \"" << segments[i] << "\"\n";
	//}

}

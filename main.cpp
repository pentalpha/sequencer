#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

#include "StringPair.h"
#include "StringOperations.h"
#include "ProcessBucket.h"

using namespace std;

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

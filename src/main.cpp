//#define NDEBUG
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

#include "StringPair.h"
#include "StringOperations.h"
#include "Bucket.h"

Bucket operator+(const Bucket &bucket, const Bucket &otherBucket)
{
	Bucket sum = bucket;
	sum.segments.insert(sum.segments.begin(),
						otherBucket.segments.begin(), otherBucket.segments.end());
	return sum;
}

using namespace std;

int main(int argc, char **argv){
	int segmentsPerBucket = 9;
	
	vector<string> tempSegments;
	vector<Bucket> buckets;

	string line;
	int totalSegments = 0;
	while(getline(cin, line)){
		//Caso o texto use quebras de linha do tipo "\n\r", retira as \r"
		if(line[line.size()-1] == '\r'){
			line = line.substr(0, line.size()-1);
			
			//cout << "quebra de linha barra r retirada  \n";
		}

		tempSegments.push_back(line);
		totalSegments++;
		if(tempSegments.size() == segmentsPerBucket){
			buckets.push_back(Bucket(tempSegments));
			tempSegments.clear();
		}
	}
	if(!tempSegments.empty()){
		buckets.push_back(Bucket(tempSegments));
		tempSegments.clear();
	}
	cout << "temp buckets instantiated\n";
	
	/*for(int i = 0; i < nBuckets; i++){
		buckets[i].nSegments = tempBuckets[i].size();
		buckets[i].segments = new string[buckets[i].nSegments];
		for(int j = 0; j < buckets[i].nSegments; j++){
			buckets[i].segments[j] = tempBuckets[i][j];
		}
		tempBuckets[i].clear();
	}*/
	//tempBuckets.clear();
	cout << "buckets instantiated\n";

	for(Bucket bucket : buckets){
		//cout << "Bucket " << actualBucket <<":\n";
		//cout << "the bucket " << actualBucket << " have " << buckets[actualBucket].nSegments << "." << endl;
		bucket.process(false);
		//nSegmentsInBucket[actualBucket] = nSegments;
		//cout << "Final processing of the bucket[outside]\n";
		//for (int i = 0; i < buckets[actualBucket].nSegments; i++){
		// 	cout << "segments[" << i << "] = \"" << buckets[actualBucket].segments[i] << "\"\n";
		//}
		//cout << "the bucket " << actualBucket << " now have " << buckets[actualBucket].nSegments << "." << endl;
	}
	
	int segmentsLeft = 0;
	for(Bucket bucket : buckets){
		segmentsLeft += bucket.nSegments();
	}
	cout << segmentsLeft << " segments left in total." << endl;
	Bucket finalBucket;
	//finalBucket.segments = new string[segmentsLeft];
	//finalBucket.nSegments = segmentsLeft;
	int index = 0;
	
	for(Bucket bucket : buckets){
		finalBucket = finalBucket + bucket;
	}

	cout << "Bucket final:\n";
	finalBucket.process(true);
	string textoSaida = "";
	//for (int i = 0; i < finalBucket.segments.size(); i++){
	//	textoSaida += "[] - " + finalBucket.segments[i] + "\n";
	//}
	textoSaida = finalBucket.segments[0];
	//replace(textoSaida.begin(),textoSaida.end(),"%%","\n");
	
	
	//substituir os %% por \n
	for(int i = 0; i < textoSaida.size()-1; i++){
		if((textoSaida[i] == '%') && (textoSaida[i+1] == '%')){
			textoSaida.replace(i,2,"\n");
		}
	}

	cout << textoSaida;

	return 0;
}

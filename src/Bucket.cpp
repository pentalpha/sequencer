#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <map>

#include "StringPair.h"
#include "StringOperations.h"
#include "Bucket.h"

using namespace std;

void Bucket::process(bool forceMerge){
	map<StringPair, CompareResult> hashmap;
	bool merged = false;
	int iteration = 0;
	do{
		StringPair* keyMax = NULL;
		
		for(int i = 1; i < segments.size(); i++){
			for(int j = 0; j < i; j++){
				StringPair key = StringPair(segments[i], segments[j]);
				if(hashmap.find(StringPair(segments[i], segments[j])) == hashmap.end()){
					hashmap[key] = CompareResult(segments[i], segments[j], true);
				}
				if(hashmap[key].haveResult()){
					if(keyMax == NULL){
						keyMax = new StringPair();
						*keyMax = key;
					}else{
						if(hashmap[key].module > hashmap[*keyMax].module){
							*keyMax = key;
						}
					} 
				}
			}
		}
		
		if(keyMax != NULL){
			segments.erase(find(segments.begin(), segments.end(), keyMax->x));
			segments.erase(find(segments.begin(), segments.end(), keyMax->y));
			segments.push_back(hashmap[*keyMax].result);
			segments = segments;
			merged = true;
		}
		iteration++;
	}while(segments.size() > 1 && merged);
}
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include <istream>
#include <assert.h>

#include "StringPair.h"
#include "SegmentSet.h"

using namespace std;

SegmentSet::SegmentSet(istream* inputStream){
	assert(inputStream != NULL);
	
	string line;
	bool endOfFile = false;
	do{
		try{
			getline(*inputStream, line);
			//Caso o texto use quebras de linha do tipo "\n\r", retira as \r"
			if(line[line.size()-1] == '\r'){
				line = line.substr(0, line.size()-1);
				//cout << "quebra de linha barra r retirada  \n";
			}
			segments.push_back(line);
		}catch(...){
			endOfFile = true;
		}
	}while(!endOfFile);
}

string SegmentSet::getResults(){
	assert(segments.size() >= 1);
	
	string results = "";
	if(segments.size() == 1){
		results = segments[0];
	}else{
		for(auto segment : segments){
			results = results + "[]: " + segment + "\n";
		}
	}
	//transformar %% me quebras de linha
	for(int i = 0; i < results.size()-1; i++){			
		if((results[i] == '%') && (results[i+1] == '%')){
			results.replace(i,2,"\n");
		}
	}	
		
	return results;
}

bool SegmentSet::process(){
	assert(segments.size() >= 1);
	
	map<StringPair, StringMerge> affinity;
	bool merged = false;
	do{
		StringPair* keyMax = NULL;
		
		//a matriz de semelhança resultante de comparar todos os segmentos
		//com todos os segmentos seria uma matriz espelhada (matriz[i][j] == matriz[j][i])
		//por isso, iteramos apenas pela metade inferior a diagonal.
		for(int i = 1; i < segments.size(); i++){
			for(int j = 0; j < i; j++){
				StringPair key = StringPair(segments[i], segments[j]);
				//se a o par de strings ainda não foi comparado, comparar e armazenar
				if(affinity.find(key) == affinity.end()){
					affinity[key] = StringMerge(segments[i], segments[j], true);
				}
				//verificar se um maximo local foi encontrado
				if(affinity[key].haveResult()){
					if(keyMax == NULL){
						keyMax = new StringPair();
						*keyMax = key;
					}else{
						if(affinity[key].module > affinity[*keyMax].module){
							*keyMax = key;
						}
					} 
				}
			}
		}
		
		if(keyMax != NULL){
			//apagar o par de segmentos que foi decidido fundir em um só
			segments.erase(find(segments.begin(), segments.end(), keyMax->x));
			segments.erase(find(segments.begin(), segments.end(), keyMax->y));
			//inserir o par de segmentos agora unido como um só
			segments.push_back(affinity[*keyMax].result);
			merged = true;
		}
	}while(segments.size() > 1 && merged);
	
	return (segments.size() == 1);
}
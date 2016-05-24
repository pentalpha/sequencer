//#define NDEBUG
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <istream>
#include <map>

#include "StringPair.h"
#include "StringOperations.h"
#include "Bucket.h"
#include "Arguments.h"

using namespace std;

Bucket operator+(const Bucket &bucket, const Bucket &otherBucket)
{
        Bucket sum = bucket;
        sum.segments.insert(sum.segments.begin(),
                            otherBucket.segments.begin(), otherBucket.segments.end());
        return sum;
}

int main(int argCount, char* argVector[]){
	Arguments arguments(argCount, argVector);
	if(!arguments.helpFlag){
		istream* inputStream;
		ostream* outputStream;
		
		//seleciona a entrada de dados
		if(arguments.inputFileDefined){
			ifstream *inputFileStream = new ifstream;
			inputFileStream->open(arguments.inputFile.c_str());
			inputStream = inputFileStream;
		}else{
			inputStream = &cin;
		}
		//seleciona a saida de dados
		if(arguments.outputFileDefined){
			ofstream* outputFileStream = new ofstream;
			outputFileStream->open(arguments.outputFile.c_str(), ios::trunc);
			outputStream = outputFileStream;
		}else{
			outputStream = &cout;
		}
		//loop de leitura
		Bucket bucket;
		string line;
		while(getline(*inputStream, line)){
			//Caso o texto use quebras de linha do tipo "\n\r", retira as \r"
			if(line[line.size()-1] == '\r'){
				line = line.substr(0, line.size()-1);
				//cout << "quebra de linha barra r retirada  \n";
			}
			bucket.segments.push_back(line);
		}

		bucket.process(false);
		//cout << "Bucket final:\n";
		bucket.process(true);
		string textoSaida = bucket.segments[0];
		//for (string segment : bucket.segments){
		//	textoSaida += "[] - " + segment + "\n";
		//}
		
		//substituir os %% por \n
		for(int i = 0; i < textoSaida.size()-1; i++){
			if((textoSaida[i] == '%') && (textoSaida[i+1] == '%')){
				textoSaida.replace(i,2,"\n");
			}
		}
		*outputStream << textoSaida;
	}
	else
	{
		arguments.options->printUsage();
	}
	
	return 0;
}

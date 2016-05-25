//#define NDEBUG
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <istream>
#include <map>
#include <assert.h>

#include "StringPair.h"
#include "SegmentSet.h"
#include "Arguments.h"

using namespace std;

void sequencer(Arguments* arguments);

int main(int argCount, char* argVector[]){
	Arguments* arguments = new Arguments(argCount, argVector);
	if(!arguments->helpFlag){
		sequencer(arguments);
	}
	else
	{
		arguments->options->printUsage();
	}
	
	return 0;
}

void sequencer(Arguments* arguments){
		assert(arguments != NULL);
		
		istream* inputStream;
		ostream* outputStream;
		//seleciona a entrada de dados
		ifstream *inputFileStream;
		if(arguments->inputFileDefined){
			inputFileStream = new ifstream;
			inputFileStream->exceptions ( ifstream::failbit);
			try{
				inputFileStream->open(arguments->inputFile.c_str());
				inputStream = inputFileStream;
			}catch(ifstream::failure e){
				cout << "ERROR OPENING A INPUT FILE:" << endl;
				cout << arguments->inputFile;	
				cout << "USING CIN AS DEFAULT INPUT" << endl;
				inputStream = &cin;	
			}
			
		}else{
			inputStream = &cin;
		}
		
		//seleciona a saida de dados
		ofstream* outputFileStream;
		if(arguments->outputFileDefined){
			outputFileStream = new ofstream;
			outputFileStream->exceptions ( ofstream::failbit);
			try{
				outputFileStream->open(arguments->outputFile.c_str(), ios::trunc);
				outputStream = outputFileStream;
			}catch(ifstream::failure e){
				cout << "ERROR OPENING A OUTPUT FILE:" << endl;
				cout << arguments->outputFile;
				cout << "USING COUT AS DEFAULT OUTPUT" << endl;
				outputStream = &cout;	
			}
			
		}else{
			outputStream = &cout;
		}
		
		SegmentSet segmentSet(inputStream);
		bool successful = segmentSet.process();
		
		if(!successful){
			*outputStream << "[MULTIPLOS SEGMENTOS RESTANTES, ALGORITMO MAL SUCEDIDO]";
		}
		*outputStream << segmentSet.getResults();
		
		if(arguments->inputFileDefined) inputFileStream->close();
		if(arguments->outputFileDefined) outputFileStream->close();
}
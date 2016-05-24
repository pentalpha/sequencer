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
#include "SegmentSet.h"
#include "Arguments.h"

using namespace std;

void sequencer(Arguments arguments);

int main(int argCount, char* argVector[]){
	Arguments arguments(argCount, argVector);
	if(!arguments.helpFlag){
		sequencer(arguments);
	}
	else
	{
		arguments.options->printUsage();
	}
	
	return 0;
}

void sequencer(Arguments arguments){
		istream* inputStream;
		ostream* outputStream;
		//seleciona a entrada de dados
		ifstream *inputFileStream;
		if(arguments.inputFileDefined){
			inputFileStream = new ifstream;
			inputFileStream->open(arguments.inputFile.c_str());
			inputStream = inputFileStream;
		}else{
			inputStream = &cin;
		}
		
		//seleciona a saida de dados
		ofstream* outputFileStream;
		if(arguments.outputFileDefined){
			outputFileStream = new ofstream;
			outputFileStream->open(arguments.outputFile.c_str(), ios::trunc);
			outputStream = outputFileStream;
		}else{
			outputStream = &cout;
		}
		
		SegmentSet segmentSet(inputStream);
		bool successful = segmentSet.process();
		
		if(!successful){
			*outputStream << "[MULTIPLOS SEGMENTOS RESTANTES, ALGORITMO MAL SUCEDIDO]";
		}
		*outputStream << segmentSet.getResults();
		
		if(arguments.inputFileDefined) inputFileStream->close();
		if(arguments.outputFileDefined) outputFileStream->close();
}
#ifndef _ARGUMENTS_
#define _ARGUMENTS_

#include <string>
#include "anyoption.h"

using namespace std;

class Arguments{
public:
	AnyOption* options;
	string inputFile, outputFile;
	bool inputFileDefined, outputFileDefined;
	bool helpFlag;
	
	Arguments(int argCount, char* argVector[]){
		options = new AnyOption();
		options->addUsage("-h, --help\t\tPrints this help");
		options->addUsage("--input\t<file_name>\tSet the input file with the segments");
		options->addUsage("--output\t<file_name>\tSet the output file for the final text");
		options->setFlag("help", 'h');
		options->setOption("input");
		options->setOption("output");
		options->processCommandArgs(argCount, argVector);
	
		inputFileDefined = (options->getValue("input") != NULL);
		//if(inputFileDefined){
		//	cout << "input file defined" << endl;
		//}
		outputFileDefined = (options->getValue("output") != NULL);
		helpFlag = (options->getFlag("help") || options->getFlag('h'));
		if(inputFileDefined){
			inputFile = options->getValue("input");
		}
		if(outputFileDefined){
			outputFile = options->getValue("output");
		}
	}
};

#endif
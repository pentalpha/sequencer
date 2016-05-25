#ifndef _ARGUMENTS_
#define _ARGUMENTS_

#include <string>
#include <assert.h>
#include "anyoption.h"

using namespace std;
/**
	@brief Parses command line arguments to be used as simple bools and strings
	@author Pitágoras Alves
	@date May 2016
*/
class Arguments{
public:
	AnyOption* options;
	string inputFile, outputFile;
	bool inputFileDefined, outputFileDefined;
	bool helpFlag;
	
	/**
		Constructor for the class Arguments
		@param	argCount	Number of arguments
		@param	argVector	Array with the arguments in c strings
	*/
	Arguments(int argCount, char* argVector[]){
		assert(argCount >= 0);
		assert(argVector != NULL);
		
		options = new AnyOption();
		options->addUsage("-h, --help\t\tPrints this help");
		options->addUsage("--input\t<file_name>\tSet the input file with the segments");
		options->addUsage("--output\t<file_name>\tSet the output file for the final text");
		options->setFlag("help", 'h');
		options->setOption("input");
		options->setOption("output");
		options->processCommandArgs(argCount, argVector);
	
		inputFileDefined = (options->getValue("input") != NULL);
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
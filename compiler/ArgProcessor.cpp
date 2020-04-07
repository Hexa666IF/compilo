/*******************************************************************************************
Créé le : 07 Avril 2020
par : sadsitha
e-mail : sadsitha.lokuge@insa-lyon.fr
*******************************************************************************************/


#include "ArgProcessor.h"

//------------- public methods ---------------------------------------------------------

std::string ArgProcessor::getAsmChoice()
{
	return asm_choice;
}

std::string ArgProcessor::getFilePath()
{
	return file_path;
}
//------------- Constructor / Destructors ------------------------------------------------

ArgProcessor::ArgProcessor(int argn, const char **argv)
{
	if (argn>=2) {
		int pathIndex = 1;
		if (argn==3) {
			pathIndex = 2;
			asm_choice = argv[1];
		}
		ifstream lecture(argv[pathIndex]);
		in << lecture.rdbuf();

	}
}	

//------------- Protected methods ---------------------------------------------------------

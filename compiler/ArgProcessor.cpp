/*******************************************************************************************
Créé le : 07 Avril 2020
par : sadsitha
e-mail : sadsitha.lokuge@insa-lyon.fr
*******************************************************************************************/

#include <algorithm>
#include <sstream>
#include <iterator>

#include "ArgProcessor.h"

//------------- public methods ---------------------------------------------------------

static std::string ArgProcessor::getAsmChoice()
{
	return asm_choice;
}

static std::string ArgProcessor::getFilePath()
{
	return file_path;
}
//------------- Constructor / Destructors ------------------------------------------------

ArgProcessor::ArgProcessor(int argn, const char **argv)
{
	//defaults
	file_path = "";
	asm_choice = "x86";

	for (int i=argn-1; i>=0; --i) 
	{
		std::string value = argv[i];
		if (i==argn-1) {
			file_path = value;
		} else if (i==argn-2) {
			std::stringstream ss(value);
			std::string token;
			std::string option;
			while (std::getline(ss, token, '=')) {
				option=token;
			}
			asm_choice=option;
		};
   
	}
}



//------------- Protected methods ---------------------------------------------------------

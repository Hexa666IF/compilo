/*******************************************************************************************
Créé le : 07 Avril 2020
par : sadsitha
e-mail : sadsitha.lokuge@insa-lyon.fr
*******************************************************************************************/

#include <algorithm>
#include <sstream>
#include <iterator>
#include <string>

#include "ArgProcessor.h"

//------------- static initialisation --------------------------------------------------

std::map<std::string, std::string> ArgProcessor::argMap;

//------------- public methods ---------------------------------------------------------


std::string ArgProcessor::getArg(std::string key)
{
	std::string value = "";
	try 
	{ 
		value = argMap.at(key);
	} catch (const std::out_of_range& e) 
	{ 
		value="";
	}
	
	return value;
}
//------------- Constructor / Destructors ------------------------------------------------

ArgProcessor::ArgProcessor(int argn, const char **argv)
{
	// Insert default args here
	argMap.insert(std::pair<std::string, std::string>("target", "x86"));
	argMap.insert(std::pair<std::string, std::string>("file_path", ""));  

	for (int i=argn-1; i>0; --i) 
	{
		std::string key = argv[i];
		std::string value = argv[i];

		if (i==argn-1) { // map target file_path
			argMap.at("file_path") = value;
		} else { // map other options
			std::stringstream ss(value);
			std::string token;
			for (int j=0; std::getline(ss, token, '='); ++j) {
				switch (j)
				{
					case 0:
						key = token.erase(0,2);
						break;
					case 1:
						value = token;
						break;
					default:
						break;
				}
			}
			setMapValue(key,value);
		};
   
	}
}



//------------- Protected methods ---------------------------------------------------------

void ArgProcessor::setMapValue(std::string key, std::string value)
{
	std::map<std::string, std::string>::iterator it = argMap.find(key); 
	if (it != argMap.end()){
		(*it).second = value; 
	}else{
		argMap.insert(std::pair<std::string, std::string>(key, value));
	}
}
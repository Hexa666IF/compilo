/******************************************************************
Créé le : 07 Avril 2020
par : sadsitha
e-mail : sadsitha.lokuge@insa-lyon.fr
******************************************************************/

#if ! defined ( ARGPROC_H )
#define ARGPROC_H

#include <map> 

// class used for managing commandline parameters
class ArgProcessor
{
	public:

	//----- static variables -----
		// map for storing arguments
		static std::map<std::string, std::string> argMap;

	//----- public methods -----
		// get argMap value from key
		static std::string getArg(std::string key);

	//--- Constructors / Destructor ---
		ArgProcessor(int argn, const char **argv);

	protected:
	//----- protected methods -----
		// set argMap value
		void setMapValue(std::string key, std::string value);

	//----- protected attributes -----
	
};

#endif // ! defined ( ARGPROC_H )

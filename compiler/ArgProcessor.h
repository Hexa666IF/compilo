/******************************************************************
Créé le : 07 Avril 2020
par : sadsitha
e-mail : sadsitha.lokuge@insa-lyon.fr
******************************************************************/

#if ! defined ( ARGPROC_H )
#define ARGPROC_H

// class used for processing commandline parameters
class ArgProcessor
{
	public:

	//----- static variables -----
		static std::string asm_choice;
		static std::string file_path;

	//----- public methods -----
		static std::string getAsmChoice();
		static std::string getFilePath();

	//--- Constructors / Destructor ---
		ArgProcessor(int argn, const char **argv);

	protected:
	//----- protected methods -----

	//----- protected attributes -----


};

#endif // ! defined ( ARGPROC_H )

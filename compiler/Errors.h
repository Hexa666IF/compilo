/******************************************************************
Créé le : 25 mars 2020
par : Solal
e-mail :
******************************************************************/

#if ! defined ( ERRORS_H )
#define ERRORS_H

#include <iostream>
#include <vector>
#include <string>

// class used to store and print the errors met during the compilation
class Errors
{
	public:

	//----- public methods -----

		// Add an error in the list
		static void addError(int code, std::string var);

		// Print the errors stored in the list, return true if there was errors
		static bool printErrors();

		static int getErrorCode();

	//---- overloaded operators ----
	//--- Constructors / Destructor ---

	protected:
	//----- protected methods -----
	//----- protected attributes -----
		static std::vector<std::string> errorsList;
        static int errorCode; // Errore code return by the program


};

#endif // ! defined ( ERRORS_H )

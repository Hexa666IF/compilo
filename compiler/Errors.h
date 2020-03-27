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

enum ErrorCode { lexerSyntaxError = -2, parserSyntaxError, errorFree, notDeclared, notInitialised, multipleDeclaration, notUsed };

// class used to store and print the errors met during the compilation
class Errors
{
	public:

	//----- public methods -----

		// Add an error in the list
		static void addError(std::string var, ErrorCode code);

		// Print the errors stored in the list, return true if there was errors
		static bool printErrors();

	//---- overloaded operators ----
	//--- Constructors / Destructor ---

	protected:
	//----- protected methods -----
	//----- protected attributes -----
		static std::vector<std::pair<std::string, ErrorCode>> errorsList;


};

#endif // ! defined ( ERRORS_H )

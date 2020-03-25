/*******************************************************************************************
Créé le : 25 mars 2020
par : Solal
e-mail :
*******************************************************************************************/

#include "Errors.h"

using namespace std;

//------------- public methods -------------------------------------------------

void Errors::addError(int code, std::string var)
{
    string error;
	switch (code)
    {
    case 1:
        error = "ERROR : The variable "+var+" is used but not declared.";
        Errors::errorsList.push_back(error);
        Errors::errorCode = 1;
        break;
    case 2:
        error = "ERROR : The variable "+var+" is declared at least twice.";
        Errors::errorsList.push_back(error);
        Errors::errorCode = 2;
        break;
    case 3:
        error = "WARNING : The variable "+var+" is unused.";
        Errors::errorsList.push_back(error);
        Errors::errorCode = 3;
        break;
    
    default:
        break;
    }
}

bool Errors::printErrors()
{
    bool print = false;

    for(int i = 0; i < Errors::errorsList.size(); i++)
    {
        cout << Errors::errorsList[i] << endl;
        cout << endl;
        print = true;
    }
    
    return print;
}

int Errors::getErrorCode()
{
    return Errors::errorCode;
}
//------------- Protected Attributes ------------------------------------
std::vector<std::string> Errors::errorsList;
int Errors::errorCode;
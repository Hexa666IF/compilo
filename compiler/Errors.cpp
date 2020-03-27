/*******************************************************************************************
Créé le : 25 mars 2020
par : Solal
e-mail :
*******************************************************************************************/

#include "Errors.h"

using namespace std;

//------------- Protected Attributes ------------------------------------
std::vector<std::pair<std::string, ErrorCode>> Errors::errorsList;

//------------- public methods -------------------------------------------------

void Errors::addError(std::string var, ErrorCode code)
{
	switch (code)
    {
    case notDeclared:
        Errors::errorsList.push_back(make_pair(var, notDeclared));
        break;

    case notInitialised:
        Errors::errorsList.push_back(make_pair(var, notInitialised));
        break;

    case multipleDeclaration:
        Errors::errorsList.push_back(make_pair(var, multipleDeclaration));
        break;

    case notUsed:
        Errors::errorsList.push_back(make_pair(var, notUsed));
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
        switch (errorsList[i].second)
        {
        case notDeclared:
            cerr << "ERROR : The variable "+errorsList[i].first+" is used but not declared." << endl;
            cerr << endl;
            break;

        case notInitialised:
            cerr << "ERROR : The variable "+errorsList[i].first+" is used but not initialised." << endl;
            cerr << endl;
            break;

        case multipleDeclaration:
            cerr << "ERROR : The variable "+errorsList[i].first+" is declared at least twice." << endl;
            cerr << endl;
            break;

        case notUsed:
            cerr << "WARNING : The variable "+errorsList[i].first+" is unused." << endl;
            cerr << endl;
            break;

        default:
            break;
        }

        print = true;
    }
    
    return print;
}

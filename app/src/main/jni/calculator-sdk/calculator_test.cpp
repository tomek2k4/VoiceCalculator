 
//************************************************************
//************************************************************
//**														**
//**	Title:		    SequencialCalculator Test main				**
//** 	Device / Size:	                					**
//**	Programmed by:										**
//**	Copyright (c):	Tomasz Maslon 						**
//**					All rights reserved					**
//**														**
//**														**
//************************************************************
//************************************************************

#include <iostream>
#include <string>
#include <list>
#include "RPNBuilder.h"
#include "ICalculator.h"
#include "SequencialCalculator.h"


//**********************************************************************************************************************************************
//**********************************************************************************************************************************************
//**********************************************************************************************************************************************
//**********************************************************************************************************************************************
//**********************************************************************************************************************************************
//**********************************************************************************************************************************************
//**********************************************************************************************************************************************

using namespace std;

//***********************************
//***********************************
//******* TEST MAIN FUNCTION ********
//***********************************
//***********************************
int main(int argc, char **argv)
{
	cout << "This is calculator's test main function" << endl;
	std:list<string> expressionsList;
	expressionsList.push_back("1+3*2=");
	expressionsList.push_back("1*3+2=");
	expressionsList.push_back("11*13+24*54=");


	string expression;

	for (std::list<string>::iterator it=expressionsList.begin(); it != expressionsList.end(); ++it)
	{
		RPNBuilder rpnBuilder;
		cout << "Initial output:" <<rpnBuilder.getOutput()<<endl;
		expression = *it;
		rpnBuilder.enter(expression);
		cout << expression << " is " << rpnBuilder.getOutput()<<" in reverse polish notation"<<endl;
	}

	ICalculator *calc = new SequencialCalculator();
	for (std::list<string>::iterator it=expressionsList.begin(); it != expressionsList.end(); ++it)
	{
		calc->clear();
		cout << "Initial calc output:" <<calc->getOutput()<<endl;
		expression = *it;
		calc->enter(expression);
		cout << expression << " is " << calc->getOutput()<<endl;
	}


	delete calc;
	return 0;
}








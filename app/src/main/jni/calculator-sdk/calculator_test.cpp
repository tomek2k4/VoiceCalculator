 
//************************************************************
//************************************************************
//**														**
//**	Title:  SequenceCalculator Test main	    		**
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
#include "SequenceCalculator.h"
#include "RPNCalculator.h"


//**********************************************************************************************************************************************
//**********************************************************************************************************************************************
//**********************************************************************************************************************************************
//**********************************************************************************************************************************************
//**********************************************************************************************************************************************
//**********************************************************************************************************************************************
//**********************************************************************************************************************************************

using namespace std;

string rpnBuilderOutputToString(queue<string> rpnOutput)
{
	string prefix = "";
	string outStr;
	while(!rpnOutput.empty())
	{
		outStr+=prefix;
		outStr+=rpnOutput.front();
		prefix = " ";
		rpnOutput.pop();
	}
	return outStr;
}




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
	expressionsList.push_back("2^3=");


	string expression;
	cout<< "******************"<<" RPN builder test:"<< "******************"<<endl;
	for (std::list<string>::iterator it=expressionsList.begin(); it != expressionsList.end(); ++it)
	{
		RPNBuilder rpnBuilder;
		cout << "Initial output:" << rpnBuilderOutputToString(rpnBuilder.getOutput())<<endl;
		expression = *it;
		rpnBuilder.enter(expression);
		cout << expression << " is " << rpnBuilderOutputToString(rpnBuilder.getOutput())<<" in reverse polish notation"<<endl;
	}

	cout<< "******************"<<" Sequential calcualtor test:"<< "******************"<<endl;
	ICalculator *calc = new SequenceCalculator();
	for (std::list<string>::iterator it=expressionsList.begin(); it != expressionsList.end(); ++it)
	{
		calc->clear();
		cout << "Initial calc output:" <<calc->getOutput()<<endl;
		expression = *it;
		calc->enter(expression);
		cout << expression << calc->getOutput()<<endl;
	}
	delete calc;

	cout<< "******************"<<" Reverse Polish Notation calcualtor test:"<< "******************"<<endl;
	calc = new RPNCalculator();
	for (std::list<string>::iterator it=expressionsList.begin(); it != expressionsList.end(); ++it)
	{
		calc->clear();
		cout << "Initial calc output:" <<calc->getOutput()<<endl;
		expression = *it;
		calc->enter(expression);
		cout << expression << calc->getOutput()<<endl;
	}
	delete calc;

	return 0;
}








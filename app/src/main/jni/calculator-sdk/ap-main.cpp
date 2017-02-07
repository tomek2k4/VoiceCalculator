 
//************************************************************
//************************************************************
//**														**
//**	Title:		    Calculator Test main				**
//** 	Device / Size:	                					**
//**	Programmed by:										**
//**	Copyright (c):	Tomasz Maslon 						**
//**					All rights reserved					**
//**														**
//**														**
//************************************************************
//************************************************************

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "Calculator.h"
#include "RPNBuilder.h"


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
//********** MAIN FUNCTION **********
//***********************************
//***********************************
int main(int argc, char **argv)
{
	cout << "This is calculator's test main function" << endl;

//	Calculator *c = new Calculator();
//
//	cout << "Initial output:" << c->getOutput() << endl;
////    c->enter("2+3=");
////    cout << "2+3=" << c->getOutput()<< endl;
////    c->enter("10-4=");
////    cout << "10-4=" << c->getOutput()<< endl;
//	  c->enter("1+3*2=");
//	  cout << "1+3*2=" << c->getOutput()<< endl;
//	  printf("output=%s\n",c->getOutput().c_str());
//
//    delete c;

	std::string expression;
	{
		RPNBuilder rpnBuilder;
		cout << "Initial output:" <<rpnBuilder.getOutput()<<endl;
		expression = "1+3*2=";
		rpnBuilder.enter(expression);
		cout << expression << " is \"" << rpnBuilder.getOutput()<<"\" in reverse polish notation"<<endl;
	}

	{
		RPNBuilder rpnBuilder;
		cout << "Initial output:" <<rpnBuilder.getOutput()<<endl;
		expression = "1*3+2=";
		rpnBuilder.enter(expression);
		cout << expression << " is \"" << rpnBuilder.getOutput() <<"\" in reverse polish notation" << endl;
	}

	{
		RPNBuilder rpnBuilder;
		cout << "Initial output:" <<rpnBuilder.getOutput()<<endl;
		expression = "11*13+24*54=";
		rpnBuilder.enter(expression);
		cout << expression << " is \"" << rpnBuilder.getOutput() <<"\" in reverse polish notation" << endl;
	}



	return 0;
}








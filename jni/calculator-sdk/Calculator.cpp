/*
 * Calculator.cpp
 *
 *  Created on: 16 sty 2017
 *      Author: tomasz
 */

#include <sstream>
#include <iostream>
#include <strings.h>
#include <stdio.h>
#include "Calculator.h"

using namespace std;

const string Calculator::VALID_OPERATIONS = "+-*";

/**
 * Constructor
 */
Calculator::Calculator():oper('0'),state(ON)
{
	output = new stringstream();
	*output<<'0';
}

string Calculator::getOutput()
{
	//cout << "Calling getOutput()"<<endl;
	return output->str();
}

void Calculator::enter(string expr)
{
	//cout << "Calling enter()"<<endl;
	for(int k=0; k < expr.length(); k++){
		//cout << "Enter for "<<k<<" element,which is "<<expr.at(k)<<endl;
		enter(expr.at(k));
	}
}



void Calculator::enter(char c)
{
	switch (state) {
		case ON:
			enterON(c);
			break;
		case INP:
			enterINP(c);
			break;
		case OPER:
			enterOPER(c);
			break;
	}
}

void Calculator::enterON(char c)
{
	//cout << "Entering ON with c="<<c<<endl;
	if(isdigit(c))
	{
		//cout << "First char is digit"<<endl;
		acc = new stringstream();
		*acc<<c;
		if(output!=NULL)
			delete output;
		output = new stringstream();
		*output<<c;
		state = INP;
	}
}

void Calculator::enterINP(char c)
{
	//cout << "Entering INP with c="<<c<<endl;
	if(isdigit(c))
	{
		*acc<<c;
		*output<<c;
		state = INP;
	}
	else if(VALID_OPERATIONS.find(c)!=string::npos )
	{
		//cout << "c="<<c<<" is valid operator"<<endl;
		oper = c;
		if(output!=NULL)
			delete output;
		output = new stringstream();
		//cout << "output was reinitialized"<<endl;
		*output << acc->str() << oper;
		//cout << "output: "<<output->str()<<endl;
//		if(arg!=NULL)
//			delete arg;
		arg = new stringstream();
		//cout << "arg was reinitialized"<<endl;
		*arg << 0;
		state = OPER;
	}
}

void Calculator::enterOPER(char c)
{
	//cout << "Entering OPER with c="<<c<<endl;
    if (isdigit(c)) {
        *arg<<c;
		if(output!=NULL)
			delete output;
        output = new stringstream(arg->str());
        state = OPER;
    } else if (VALID_OPERATIONS.find(c)!=string::npos) {
        state = OPER;
        calculate();
        oper = c;
    } else if (c == '=') {
        calculate();
        state = OPER;
    }
}

void Calculator::calculate()
{
	//cout << "Entering calculate"<<endl;
	int a,b,result;
	std::istringstream astringstream(acc->str());
	astringstream >> a;
	std::istringstream bstringstream(arg->str());
	bstringstream >> b;
	switch (oper) {
		case '+':
			result = a + b;
			break;
		case '-':
			result = a - b;
			break;
		case '*':
			result = a * b;
			break;
	}

	if(output!=NULL)
		delete output;
    output = new stringstream();
    *output << result;
	if(acc!=NULL)
		delete acc;
    acc = new stringstream();
    *acc << result;
	if(arg!=NULL)
		delete arg;
    arg = new stringstream("0");

}



/**
 * Destructor
 */
Calculator::~Calculator()
{
	if(output!=NULL)
		delete output;
	if(acc!=NULL)
		delete acc;
	if(arg!=NULL)
		delete arg;
}



/*
 * Calculator.cpp
 *
 *  Created on: 16 sty 2017
 *      Author: tomasz
 */

#include <sstream>
#include <iostream>
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
	arg = new stringstream();
	*output<<"0";
}

string Calculator::getOutput()
{
	return output->str();
}

void Calculator::enter(string expr)
{
	for(int k=0; k < expr.length(); k++){
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
	if(iswdigit(c))
	{
		acc = new stringstream();
		*acc<<c;
		clearStream(output);
		*output<<c;
		state = INP;
	}
}

void Calculator::enterINP(char c)
{
	if(iswdigit(c))
	{
		*acc<<c;
		*output<<c;
		state = INP;
	}
	else if(VALID_OPERATIONS.find(c)!=string::npos )
	{
		oper = c;
		clearStream(output);
		*output << acc << oper;
		clearStream(arg);
		*arg << 0;
		state = OPER;
	}
}

void Calculator::enterOPER(char c)
{
    if (iswdigit(c)) {
        *arg<<c;
		clearStream(output);
        *output << arg;
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

	clearStream(output);
    *output << result;
    clearStream(acc);
    *acc << result;
	clearStream(arg);
    *arg<<"0";
}


void Calculator::clearStream(stringstream* stream)
{
    stream->str( std::string() );
	stream->clear();
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



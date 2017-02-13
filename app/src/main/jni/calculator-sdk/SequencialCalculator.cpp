/*
 * Calculator.cpp
 *
 *  Created on: 16 sty 2017
 *      Author: tomasz
 */

#include <sstream>
#include <iostream>
#include "ICalculator.h"
#include "SequencialCalculator.h"

using namespace std;

const string SequencialCalculator::VALID_OPERATIONS = "+-*";

/**
 * Constructor
 */
SequencialCalculator::SequencialCalculator():oper('0'),state(ON)
{
	output="0";
}

string SequencialCalculator::getOutput()
{
	return output;
}

void SequencialCalculator::enter(string expr)
{
	for(int k=0; k < expr.length(); k++)
	{
		enter(expr.at(k));
	}
}

void SequencialCalculator::enter(char c)
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

void SequencialCalculator::clear()
{

	output.clear();
	output = "0";
	acc.clear();
	arg.clear();
	oper = '0';
	state = ON;
}



void SequencialCalculator::enterON(char c)
{
	if(iswdigit(c))
	{
		acc+=c;
		output+=c;
		state = INP;
	}
}

void SequencialCalculator::enterINP(char c)
{
	if(iswdigit(c))
	{
		acc+=c;
		output+=c;
		state = INP;
	}
	else if(VALID_OPERATIONS.find(c)!=string::npos )
	{
		oper = c;
		output.clear();
		output+=acc;
		output+=oper;
		arg.clear();
		arg = "0";
		state = OPER;
	}
}

void SequencialCalculator::enterOPER(char c)
{
    if (iswdigit(c)) {
        arg+=c;
		output = arg;
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

void SequencialCalculator::calculate()
{
	int a,b,result;
	std::istringstream astringstream(acc);
	astringstream >> a;
	std::istringstream bstringstream(arg);
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

	stringstream out;
	out<<result;
	output = out.str();

	stringstream accss;
	accss<<result;
	acc = accss.str();

    arg = "0";
}


/**
 * Destructor
 */
SequencialCalculator::~SequencialCalculator()
{
}



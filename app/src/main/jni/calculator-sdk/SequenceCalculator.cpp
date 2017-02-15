/*
 * Calculator.cpp
 *
 *  Created on: 16 sty 2017
 *      Author: tomasz
 */

#include <sstream>
#include <iostream>
#include "ICalculator.h"
#include "SequenceCalculator.h"

using namespace std;

const string SequenceCalculator::VALID_OPERATIONS = "+-*";

/**
 * Constructor
 */
SequenceCalculator::SequenceCalculator():oper('0'),state(ON)
{
	output="0";
}

string SequenceCalculator::getOutput()
{
	return output;
}

void SequenceCalculator::enter(string expr)
{
	for(int k=0; k < expr.length(); k++)
	{
		enter(expr.at(k));
	}
}

void SequenceCalculator::enter(char c)
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

void SequenceCalculator::clear()
{

	output.clear();
	output = "0";
	acc.clear();
	arg.clear();
	oper = '0';
	state = ON;
}



void SequenceCalculator::enterON(char c)
{
	if(iswdigit(c))
	{
		acc+=c;
		output+=c;
		state = INP;
	}
}

void SequenceCalculator::enterINP(char c)
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

void SequenceCalculator::enterOPER(char c)
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

void SequenceCalculator::calculate()
{
	int a,b,result;
	std::istringstream astringstream(acc);
	astringstream >> a;
	std::istringstream bstringstream(arg);
	bstringstream >> b;

	result = ICalculator::calculate(a,b,oper);

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
SequenceCalculator::~SequenceCalculator()
{
}



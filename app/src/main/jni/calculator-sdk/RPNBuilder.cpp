//
// Created by tmaslon on 1/24/2017.
//

#include "RPNBuilder.h"

using namespace std;

const string RPNBuilder::HIGH_PRIORITY_OPERATIONS = "*";
const string RPNBuilder::LOW_PRIORITY_OPERATIONS = "+-";
const string RPNBuilder::VALID_OPERATIONS = LOW_PRIORITY_OPERATIONS + HIGH_PRIORITY_OPERATIONS;


/**
 * Constructor
 */
RPNBuilder::RPNBuilder():oper('0'),state(ON)
{
    output<<string();   //initialize with empty string
}

string RPNBuilder::getOutput()
{
    return output.str();
}


void RPNBuilder::enter(string expr)
{
    for(int k=0; k < expr.length(); k++){
        enter(expr.at(k));
    }
}


void RPNBuilder::enter(char c)
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

void RPNBuilder::enterON(char c)
{
    if(iswdigit(c)){
        output<<c;
        state = INP;
    }
}

void RPNBuilder::enterINP(char c)
{
    if(iswdigit(c))
    {
        output<<c;
        state = INP;
    }
    else if(VALID_OPERATIONS.find(c)!=string::npos)
    {
        oper = c;
        if(LOW_PRIORITY_OPERATIONS.find(c)!=string::npos)
        {
            while( !operStack.empty() && HIGH_PRIORITY_OPERATIONS.find(operStack.top())!=string::npos )
            {
                output<<" "<<operStack.top();
                operStack.pop();
            }
        }
        state = OPER;
    }
    else if(c == '=')
    {
        build();
        state = INP;
    }
}

void RPNBuilder::enterOPER(char c)
{
    if(iswdigit(c)){
        output<<" "<<c;
        operStack.push(oper);
        state = INP;
    }
}


void RPNBuilder::build()
{
    while(!operStack.empty())
    {
        output<<" "<<operStack.top();
        operStack.pop();
    }
}

/**
 * Destructor
 */
RPNBuilder::~RPNBuilder()
{
}




//
// Created by Tomasz Maslon on 14.02.2017.
//

#include <iostream>
#include "RPNCalculator.h"

using namespace std;
/**
 * Constructor
 */
RPNCalculator::RPNCalculator():output("0")
{
}

string RPNCalculator::getOutput()
{
    return output;
}

void RPNCalculator::clear()
{
    rpnBuilder.clear();
    output = "0";
}

void RPNCalculator::enter(std::string infixExpression)
{
    rpnBuilder.enter(infixExpression);
    expresionQueue = rpnBuilder.getOutput();

    calculate();
}

void RPNCalculator::calculate() {
    int num, a, b, result;
    string validOper = RPNBuilder::getValidOperations();
    int i = 0;
    while (!expresionQueue.empty()) {
        string lit = expresionQueue.front();
        //cout<<"Literal "<<i<<": "<<lit;
        if (is_number(lit)) {
            //cout<<" is number,push to stack"<<endl;
            istringstream(lit) >> num;
            equationStack.push(num);
        } else {
            if (validOper.find(lit) != string::npos) {
                //cout<<" is valid operand";
                a = equationStack.top();
                equationStack.pop();
                b = equationStack.top();
                equationStack.pop();
                result = ICalculator::calculate(a, b, lit.at(0));
                //cout <<" calculate: "<<a<<lit<<b<<" is "<<result;

                // push result to stack
                equationStack.push(result);
                //cout<<",push "<<result<<" on stack"<<endl;
            }
        }
        expresionQueue.pop();
        i++;
    }

    stringstream outStream;
    // final result left on stack
    outStream<<equationStack.top();
    output = outStream.str();
}

bool RPNCalculator::is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && iswdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

/**
 * Destructor
 */
RPNCalculator::~RPNCalculator()
{
}

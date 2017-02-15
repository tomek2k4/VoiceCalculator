//
// Created by Tomasz Maslon on 14.02.2017.
//

#ifndef VOICECALCULATOR_RPNCALCULATOR_H
#define VOICECALCULATOR_RPNCALCULATOR_H


#include <string>
#include "ICalculator.h"
#include "RPNBuilder.h"

class RPNCalculator : public ICalculator
{
public:
    /*
     * Constructor
     */
    RPNCalculator();


    /*
     * Gets the output of calculator
     */
    std::string getOutput();

    /*
     * entry point for equation
     */
    void enter(std::string);

    /*
     * Clear output
     */
    void clear();

    /*
     * Destructor
     */
    ~RPNCalculator();

private:
    void calculate();

    bool is_number(const std::string&);

    RPNBuilder rpnBuilder;
    std::stack<int> equationStack;
    std::queue<std::string> expresionQueue;
    std::string output;

};


#endif //VOICECALCULATOR_RPNCALCULATOR_H

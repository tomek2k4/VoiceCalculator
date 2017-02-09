//
// Created by tmaslon on 1/24/2017.
//

#ifndef RPNBUILDER_H
#define RPNBUILDER_H

#include <string>
#include <sstream>
#include <stack>
#include <queue>

class RPNBuilder
{
public:
    /*
     * Constructor
     */
    RPNBuilder();

    /*
     * Gets the output of calculator
     */
    std::string getOutput();

    /*
     * entry point for equation
     */
    void enter(std::string);

    /*
     * Destructor
     */
    ~RPNBuilder();

private:
    void enter(char c);

    void enterON(char c);

    void enterINP(char c);

    void enterOPER(char c);

    void build();

    std::queue<std::string> output;
    std::stack<char> operStack;
    std::string acc;
    char oper;

    enum State { ON, INP, OPER };

    State state;

    static const std::string VALID_OPERATIONS;
    static const std::string HIGH_PRIORITY_OPERATIONS;
    static const std::string LOW_PRIORITY_OPERATIONS;


};

#endif //RPNBUILDER_H

/*
 * Calculator.h
 *
 *  Created on: 16 sty 2017
 *      Author: tomasz
 */

#ifndef CALCULATOR_H_
#define CALCULATOR_H_


class Calculator
{
public:
	/*
	 * Constructor
	 */
	Calculator();


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
	~Calculator();



private:
	void enter(char c);

	void enterON(char c);

	void enterINP(char c);

	void enterOPER(char c);

	void calculate();

	void clearStream(std::stringstream *);

	std::stringstream *output;
	std::stringstream *acc;
	std::stringstream *arg;
	char oper;

	enum State { ON, INP, OPER };

	State state;

	static const std::string VALID_OPERATIONS;
};
#endif /* CALCULATOR_H_ */

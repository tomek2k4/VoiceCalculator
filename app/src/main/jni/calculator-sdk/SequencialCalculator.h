/*
 * Calculator.h
 *
 *  Created on: 16 sty 2017
 *      Author: tomasz
 */

#ifndef CALCULATOR_H_
#define CALCULATOR_H_


#include <queue>
#include <list>

class SequencialCalculator : public ICalculator
{
public:
	/*
	 * Constructor
	 */
	SequencialCalculator();


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
	~SequencialCalculator();



private:
	void enter(char c);

	void enterON(char c);

	void enterINP(char c);

	void enterOPER(char c);

	void calculate();

	std::string output;
	std::string acc;
	std::string arg;
	char oper;

	enum State { ON, INP, OPER };

	State state;

	static const std::string VALID_OPERATIONS;
};
#endif /* CALCULATOR_H_ */

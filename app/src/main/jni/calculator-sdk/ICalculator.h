//
// Created by Tomasz Maslon on 12.02.2017.
//

#ifndef VOICECALCULATOR_ICALCULATOR_H
#define VOICECALCULATOR_ICALCULATOR_H

class ICalculator
{
public:
    /*
    * Gets the output of calculator
    */
    virtual std::string getOutput() = 0;

    /*
     * Entry point for equation
     */
    virtual void enter(std::string) = 0;

    /*
     * Clear output
     */
    virtual void clear() = 0;

    virtual ~ICalculator() {}

};



#endif //VOICECALCULATOR_ICALCULATOR_H

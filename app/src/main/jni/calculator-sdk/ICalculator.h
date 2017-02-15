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

    inline int calculate(int a,int b,char oper)
    {
        int result;
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
        return result;
    }
};




#endif //VOICECALCULATOR_ICALCULATOR_H

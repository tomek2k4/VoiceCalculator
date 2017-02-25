/*
 * com_tomek_voicecalculator_calculator_CalculatorLib.c
 *
 *  Created on: 17 sty 2017
 *      Author: tomasz
 */

#include "com_tomek_voicecalculator_calculator_CalculatorLib.h"
#include <android/log.h>
#include <string>
#include <sstream>
#include <calculator-sdk/SequenceCalculator.h>
#include <calculator-sdk/RPNCalculator.h>
#include "handle.h"

using namespace std;

void
Java_com_tomek_voicecalculator_calculator_CalculatorLib_initialise(JNIEnv *env, jobject obj)
{
    ICalculator *inst;
    //__android_log_print(ANDROID_LOG_DEBUG, "CalculatorLib.c", "initialise;inst0=%ld", (long)inst);
    inst = new RPNCalculator();
    setHandle(env, obj, inst);
}

void
Java_com_tomek_voicecalculator_calculator_CalculatorLib_enter(JNIEnv *env, jobject obj,
                             jstring expr)
{
    ICalculator *inst = getHandle<ICalculator>(env, obj);
    const char *kstr = env->GetStringUTFChars(expr, 0);
    inst->enter(string(kstr));
    env->ReleaseStringUTFChars(expr, kstr);
}

jstring
Java_com_tomek_voicecalculator_calculator_CalculatorLib_getOutput(JNIEnv *env, jobject obj)
{
    ICalculator *inst = getHandle<ICalculator>(env, obj);
    const char *kstr = inst->getOutput().c_str();
    inst->clear();
    return env->NewStringUTF(kstr);
}


void
Java_com_tomek_voicecalculator_calculator_CalculatorLib_dispose(JNIEnv *env, jobject obj)
{
    ICalculator *inst = getHandle<ICalculator>(env, obj);
    setHandle(env, obj, (void*)0);
    delete inst;
}









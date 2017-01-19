/*
 * com_tomek_voicecalculator_calculator_CalculatorLib.c
 *
 *  Created on: 17 sty 2017
 *      Author: tomasz
 */

#include "com_tomek_voicecalculator_calculator_CalculatorLib.h"
#include <android/log.h>
#include <string>
#include <calculator-sdk/Calculator.h>
#include "handle.h"

using namespace std;

void
Java_com_tomek_voicecalculator_calculator_CalculatorLib_initialise(JNIEnv *env, jobject obj)
{
    Calculator *inst;
    __android_log_print(ANDROID_LOG_DEBUG, "CalculatorLib.c", "initialise;inst0=%ld", (long)inst);
    inst = new Calculator();
    const char *kstr = inst->getOutput().c_str();
    __android_log_print(ANDROID_LOG_DEBUG, "CalculatorLib.c", "initialise;output=%s", kstr);


    __android_log_print(ANDROID_LOG_DEBUG, "CalculatorLib.c", "initialise;inst1=%ld", (long)inst);

    setHandle(env, obj, inst);
}

void
Java_com_tomek_voicecalculator_calculator_CalculatorLib_enter(JNIEnv *env, jobject obj,
                             jstring expr)
{
    Calculator *inst = getHandle<Calculator>(env, obj);
    __android_log_print(ANDROID_LOG_DEBUG, "CalculatorLib.c", "enter;inst=%ld", (long)inst);
    const char *kstr = env->GetStringUTFChars(expr, 0);
    __android_log_print(ANDROID_LOG_DEBUG, "CalculatorLib.c", "enter;expr=%s", kstr);
    inst->enter(string(kstr));
    env->ReleaseStringUTFChars(expr, kstr);
}

jstring
Java_com_tomek_voicecalculator_calculator_CalculatorLib_getOutput(JNIEnv *env, jobject obj)
{
    Calculator *inst = getHandle<Calculator>(env, obj);
    __android_log_print(ANDROID_LOG_DEBUG, "CalculatorLib.c", "getOutput;inst=%ld", (long)inst);
    const char *kstr = inst->getOutput().c_str();
    __android_log_print(ANDROID_LOG_DEBUG, "CalculatorLib.c", "getOutput;output=%s", kstr);
    return env->NewStringUTF(inst->getOutput().c_str());
}


void
Java_com_tomek_voicecalculator_calculator_CalculatorLib_dispose(JNIEnv *env, jobject obj)
{
    Calculator *inst = getHandle<Calculator>(env, obj);
    __android_log_print(ANDROID_LOG_DEBUG, "CalculatorLib.c", "dispose;inst=%ld", (long)inst);
    setHandle(env, obj, (void*)0);
    delete inst;
}






/* Recursive implementation of the fibonacci algorithm (in a helper function) */
static jlong fib(jlong n) {
    return n <= 0 ? 0 : n == 1 ? 1 : fib(n - 1) + fib(n - 2);
}

/* Actual implementation of JNI-defined `fibNR` (recursive) function */
JNIEXPORT jlong JNICALL Java_com_tomek_voicecalculator_calculator_CalculatorLib_fibNR
  (JNIEnv *env, jclass clazz, jlong n) {
    __android_log_print(ANDROID_LOG_DEBUG, "CalculatorLib.c", "fibNR(%lld)", n);
    return fib(n);
}









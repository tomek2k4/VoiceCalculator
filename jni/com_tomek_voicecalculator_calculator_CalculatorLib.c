/*
 * com_tomek_voicecalculator_calculator_CalculatorLib.c
 *
 *  Created on: 17 sty 2017
 *      Author: tomasz
 */

#include "com_tomek_voicecalculator_calculator_CalculatorLib.h"
#include <android/log.h>


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





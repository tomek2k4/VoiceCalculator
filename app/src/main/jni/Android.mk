LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

OBJFILES := calculator-sdk/Calculator.o

LOCAL_MODULE    := com_tomek_voicecalculator_calculator_CalculatorLib

LOCAL_SRC_FILES := com_tomek_voicecalculator_calculator_CalculatorLib.cpp calculator-sdk/Calculator.cpp calculator-sdk/RPNBuilder.cpp

LOCAL_LDLIBS += -llog



include $(BUILD_SHARED_LIBRARY)

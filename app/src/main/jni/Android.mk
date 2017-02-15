LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_C_INCLUDES := calculator-sdk/ICalculator.h

OBJFILES := calculator-sdk/SequenceCalculator.o calculator-sdk/RPNCalculator.o

LOCAL_MODULE    := com_tomek_voicecalculator_calculator_CalculatorLib

LOCAL_SRC_FILES := com_tomek_voicecalculator_calculator_CalculatorLib.cpp calculator-sdk/SequenceCalculator.cpp calculator-sdk/RPNBuilder.cpp calculator-sdk/RPNCalculator.cpp

LOCAL_LDLIBS += -llog



include $(BUILD_SHARED_LIBRARY)

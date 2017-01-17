LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := com_tomek_voicecalculator_calculator_CalculatorLib

LOCAL_SRC_FILES := com_tomek_voicecalculator_calculator_CalculatorLib.c

LOCAL_LDLIBS += -llog

include $(BUILD_SHARED_LIBRARY)

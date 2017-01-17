package com.tomek.voicecalculator.calculator;

public class CalculatorLib {

	private static final String TAG = "CalculatorLib";
	
	
	//public static native void enter(String expression);
	
	public native static long fibNR(long n);
	
    static {
        // as defined by LOCAL_MODULE in Android.mk
        System.loadLibrary("com_tomek_voicecalculator_calculator_CalculatorLib");
    }
	
	
	
}

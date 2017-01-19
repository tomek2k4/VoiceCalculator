package com.tomek.voicecalculator.calculator;

public class CalculatorLib {

	private static final String TAG = "CalculatorLib";

	// handle for c++ pointer
	private long nativeHandle;
	


	public CalculatorLib(){
		initialise();
	};
	
	public native String getOutput();
	
	public native void enter(String expression);
	
	public native void dispose();

	public native void initialise();
	
	public native static long fibNR(long n);
	
    static {
        // as defined by LOCAL_MODULE in Android.mk
        System.loadLibrary("com_tomek_voicecalculator_calculator_CalculatorLib");
        System.loadLibrary("stlport_shared");
    }
	
    
}

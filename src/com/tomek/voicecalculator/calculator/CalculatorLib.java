package com.tomek.voicecalculator.calculator;

public class CalculatorLib {

	private static final String TAG = "CalculatorLib";
	private static final CalculatorLib instance = new CalculatorLib();

	// handle for c++ pointer
	private long nativeHandle;
	
	
	public native static long fibNR(long n);

	public static synchronized CalculatorLib getInstance(){
		return instance;
	}
	
	private CalculatorLib(){
		initialise();
	};
	
	public native String getOutput();
	
	public native void enter(String expression);
	
	public native void dispose();

	private native void initialise();
	
	
    static {
        // as defined by LOCAL_MODULE in Android.mk
        System.loadLibrary("com_tomek_voicecalculator_calculator_CalculatorLib");
    }
	
}

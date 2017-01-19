package com.tomek.voicecalculator;

import com.tomek.voicecalculator.calculator.CalculatorLib;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;


public class VoiceCalculatorActivity extends Activity {

	EditText input;
	TextView output;
	
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_voice_calculator);
        
        input = (EditText)findViewById(R.id.input);
        output = (TextView)findViewById(R.id.output);
    }
    
    
    public void onClickGo(View view){
    	long n = Long.parseLong(input.getText().toString());

    	long resultN = CalculatorLib.fibNR(n);
    	
    	output.append(String.format("\nfibJ(%d)=%d",n,resultN));
    	
    	String equation = "2*3+5";
    	
    	CalculatorLib calcLib = new CalculatorLib();
    	//output.append(String.format("nativeHandle1=%d",calcLib.nativeHandle));
    	calcLib.enter(equation);
    	//output.append(String.format("nativeHandle2=%d",calcLib.nativeHandle));
    	String wynik = calcLib.getOutput();
    	//output.append(String.format("nativeHandle3=%d",calcLib.nativeHandle));
    	
    	output.append(String.format("\n(%s)=%s",equation,wynik));
    	
    	calcLib.dispose();
    	
    }

}

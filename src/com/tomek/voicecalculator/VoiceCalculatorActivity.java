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
    	String expr = input.getText().toString();
    	if(expr!=null && expr.length()!=0){
    		expr += "=";
    		CalculatorLib calcLib = new CalculatorLib();
    		calcLib.enter(expr);
    		String result = calcLib.getOutput(); 		
    		output.append(String.format("\n%s%s",expr,result));
    		calcLib.dispose();	
    	}
    	
    }

}

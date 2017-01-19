package com.tomek.voicecalculator;

import java.util.ArrayList;
import java.util.Locale;

import com.tomek.voicecalculator.calculator.CalculatorLib;
import com.tomek.voicecalculator.calculator.CalculatorUtills;

import android.app.Activity;
import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.os.Bundle;
import android.speech.RecognizerIntent;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;


public class VoiceCalculatorActivity extends Activity {

	private final int SPEECH_RECOGNITION_CODE = 1;
	
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
    	startSpeechToText();
    }
    
	/**
	 * Start speech to text intent. This opens up Google Speech Recognition API dialog box to listen the speech input.
	 * */
	 private void startSpeechToText() {
		 input.setText("");
		 Intent intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
		 intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE, Locale.getDefault());
		 intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL,
				RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
		 intent.putExtra(RecognizerIntent.EXTRA_PROMPT,
				"Speak something...");
		 try {
			 startActivityForResult(intent, SPEECH_RECOGNITION_CODE);
		 } catch (ActivityNotFoundException a) {
			 Toast.makeText(getApplicationContext(),
					"Sorry! Speech recognition is not supported in this device.",
					Toast.LENGTH_SHORT).show();
		}
	 }

	 /**
	  * Callback for speech recognition activity
	  * */
	 @Override
	 protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		 super.onActivityResult(requestCode, resultCode, data);

		 switch (requestCode) {
		 case SPEECH_RECOGNITION_CODE: {
			 if (resultCode == RESULT_OK && null != data) {

				 ArrayList<String> result = data
						 .getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS);
				 String text = result.get(0);
				 input.setText(text);
				 String equation = CalculatorUtills.prepareExpression(text);
				 String calcResult = calculate(equation);
		    	 output.append(String.format("\n%s%s",equation,calcResult));
			 }
			 break;
		 }

		 }
	 }

	 private String calculate(String equation){
		 String result = "";
		 if(equation!=null && equation.length()!=0){
	    		CalculatorLib calcLib = new CalculatorLib();
	    		calcLib.enter(equation);
	    		result = calcLib.getOutput(); 		
	    		calcLib.dispose();	
	     }
		 return result;
	 }
    

}

package com.tomek.voicecalculator;

import java.util.ArrayList;
import java.util.Locale;

import com.tomek.voicecalculator.calculator.CalculatorLib;
import com.tomek.voicecalculator.calculator.CalculatorUtills;

import android.app.Activity;
import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.speech.RecognizerIntent;
import android.speech.tts.TextToSpeech;
import android.speech.tts.TextToSpeech.OnInitListener;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;


public class VoiceCalculatorActivity extends Activity implements OnInitListener {

	private final static String TAG = "VoiceCalculatorActivity";
	
	private final int SPEECH_RECOGNITION_CODE = 1;
	private final int SPEECH_SYNTHESIS_CODE = 2;
	
	private static final int CALCULATED_EXPRESSION_FINISHED_ID = 1;
	private static final int SPEECH_INPUT_FINISHED_ID = 2;
	private static final int ERROR_OCCURED_ID = 4;
	
	EditText editTextInput;
	TextView textViewOutput;

	private String result;
	
	TextToSpeech tts;

	
    private final Handler voiceCalculatorResponseHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            Log.d(TAG, "Received message on thread: " +
                    Long.valueOf(Thread.currentThread().getId()).toString());

            String handledString;
            switch (msg.what) {
            	case SPEECH_INPUT_FINISHED_ID:
            		handledString = (String) msg.obj;
            		editTextInput.setText(handledString);
            		formatAndCalculate(handledString);
            		break;
                case CALCULATED_EXPRESSION_FINISHED_ID:
                    Equation equation = (Equation) msg.obj;
   		    	 	textViewOutput.append(String.format("\n%s%s",equation.getExpression(),equation.getResult()));
   		    	 	result = equation.getResult();
   		    	 	startTextToSpeech();
                    break;
                case ERROR_OCCURED_ID:
                	handledString = (String)msg.obj;
                	Log.e(TAG,"Error: " + handledString);
                	break;
            }
        }
    };
	
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_voice_calculator);
        
        editTextInput = (EditText)findViewById(R.id.input);
        textViewOutput = (TextView)findViewById(R.id.output);

    }
    
    
    public void onClickGo(View view){
    	startSpeechToText();
    }
    
	/**
	 * Start speech to text intent. This opens up Google Speech Recognition API dialog box to listen the speech input.
	 * */
	 private void startSpeechToText() {
		 editTextInput.setText("");
		 Intent intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
		 intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE, "en-US");
		 intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL,
				RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
		 intent.putExtra(RecognizerIntent.EXTRA_PROMPT,
				"Speak your equation...");
		 try {
			 startActivityForResult(intent, SPEECH_RECOGNITION_CODE);
		 } catch (ActivityNotFoundException a) {
			 Toast.makeText(getApplicationContext(),
					"Sorry! Speech recognition is not supported in this device.",
					Toast.LENGTH_SHORT).show();
		}
	 }

	 
	/**
	 * Start speech to text intent. This opens up Google Speech Recognition API dialog box to listen the speech input.
	 * */
	 private void startTextToSpeech() {
		 tts = new TextToSpeech(this, this);
		 Intent intent = new Intent();
		 intent.setAction(TextToSpeech.Engine.ACTION_CHECK_TTS_DATA);
		 try {
			 startActivityForResult(intent, SPEECH_SYNTHESIS_CODE);
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

		 Message message;
		 switch (requestCode) {
		 case SPEECH_RECOGNITION_CODE: {
			 if (resultCode == RESULT_OK && null != data) {

				 ArrayList<String> result = data
						 .getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS);
				 String text = result.get(0);
				 
		         message = voiceCalculatorResponseHandler
		                    .obtainMessage(SPEECH_INPUT_FINISHED_ID,text);
		         voiceCalculatorResponseHandler.sendMessage(message);
			 }else{
		         message = voiceCalculatorResponseHandler
		                    .obtainMessage(ERROR_OCCURED_ID,"Speech recognition failed");
		         voiceCalculatorResponseHandler.sendMessage(message);
			 }
			 break;
		 }
		 case SPEECH_SYNTHESIS_CODE:{
			 if (resultCode == TextToSpeech.Engine.CHECK_VOICE_DATA_PASS) {
				 tts.speak("Equals "+result, TextToSpeech.QUEUE_FLUSH, null);
		     }else{
		         message = voiceCalculatorResponseHandler
		                    .obtainMessage(ERROR_OCCURED_ID,"TTS data are missing");
		         voiceCalculatorResponseHandler.sendMessage(message);
		     }
		 }
		 break;
		 }
	 }

	 private void formatAndCalculate(String text){
		 final String textFinal = text;
		 
		 new Thread(){
			 public void run(){
				 String expression = CalculatorUtills.prepareExpression(textFinal);
				 String result = "";
				 if(expression!=null && expression.length()!=0){
					 CalculatorLib calcLib = new CalculatorLib();
					 calcLib.enter(expression);
					 result = calcLib.getOutput(); 		
					 calcLib.dispose();
					 
					 Equation equation = new Equation(expression, result);
					 
			         Message message = voiceCalculatorResponseHandler
			                    .obtainMessage(CALCULATED_EXPRESSION_FINISHED_ID,equation);
			         voiceCalculatorResponseHandler.sendMessage(message);
				 }else{
			         Message message = voiceCalculatorResponseHandler
			                    .obtainMessage(ERROR_OCCURED_ID,"expression could not be obtained");
			         voiceCalculatorResponseHandler.sendMessage(message);
				 }
			 } 
		 }.start();
	 }


	@Override
	public void onInit(int status) {
		   Log.d(TAG, "OnInit - Status ["+status+"]");
		   if (status == TextToSpeech.SUCCESS) {
		     tts.setLanguage(Locale.UK);
		   }
	}
    
	private class Equation{
		private String expression;
		private String result;

		public Equation(String expression, String result) {
			this.expression = expression;
			this.result = result;
		}

		public String getExpression() {
			return expression;
		}

		public String getResult() {
			return result;
		}
		
	}
	

}

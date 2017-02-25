package com.tomek.voicecalculator;

import java.util.ArrayList;
import java.util.Locale;

import com.tomek.voicecalculator.calculator.CalculatorLib;
import com.tomek.voicecalculator.calculator.CalculatorUtills;

import android.app.Activity;
import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
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

	private String resultToSpeak;

	EditText editTextInput;
	TextView textViewOutput;

	TextToSpeech tts = null;
	CalculatorLib calcLib = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_voice_calculator);
        
        editTextInput = (EditText)findViewById(R.id.input);
        textViewOutput = (TextView)findViewById(R.id.output);

		tts = new TextToSpeech(this, this);
		calcLib = new CalculatorLib();
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
					"Sorry! Speech recognition is not supported on this device.",
					Toast.LENGTH_SHORT).show();
		}
	 }

	/**
	 * Start speech to text intent. This opens up Google Speech Recognition API dialog box to listen the speech input.
	 * */
	 private void startTextToSpeech() {
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

				 // Execute Async Task
				 new FormatTextAndCalculateTask().execute(text);
			 }else{
				 Log.e(TAG,"Error: " + "Speech recognition failed");
			 }
			 break;
		 }
		 case SPEECH_SYNTHESIS_CODE:{
			 if (resultCode == TextToSpeech.Engine.CHECK_VOICE_DATA_PASS) {
				 tts.speak("Equals "+ resultToSpeak, TextToSpeech.QUEUE_FLUSH, null);
		     }else{
				 Log.e(TAG,"Error: " + "TTS data are missing");
		     }
		 }
		 break;
		 }
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

	@Override
	protected void onDestroy() {
		super.onDestroy();
		tts.shutdown();
		calcLib.dispose();
	}


	private class FormatTextAndCalculateTask extends AsyncTask<String, Integer, Equation> {

		@Override
		protected Equation doInBackground(String... spokenTexts) {
			String spokenText = spokenTexts[0];

			Equation equation;

			String expression = CalculatorUtills.prepareExpressionForCalculation(spokenText);
			String result = "";
			if(expression!=null && expression.length()!=0){
				calcLib.enter(expression);
				// Save resultToSpeak in String after that native calc's output is cleared
				result = calcLib.getOutput();
				equation = new Equation(expression, result);
			}else{
				equation = new Equation("","0");
			}
			return equation;
		}

		@Override
		protected void onPostExecute(Equation equation) {
			textViewOutput.append(String.format("\n%s%s",equation.getExpression(),equation.getResult()));
			resultToSpeak = equation.getResult();
			startTextToSpeech();
		}
	}


}

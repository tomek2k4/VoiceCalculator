package com.tomek.voicecalculator.calculator;

public class CalculatorUtills {
	
	private final static String WHITESPACE_REGEX = "\\s+";
	private final static String NUMERIC_REGEX = "\\d+";
	
	public static String prepareExpression(String input){
		
		String expresion = transform(input);
		expresion += "=";
		
		return expresion;
	}

	private static String transform(String inp){
		String[] splitStr = inp.split(WHITESPACE_REGEX);
		StringBuilder strBuilder = new StringBuilder();
		for(String word:splitStr){
			strBuilder.append(translateWord(word));
		}
		
		return strBuilder.toString();
	}
	
	private static String translateWord(String word){
		if(word.matches(NUMERIC_REGEX)){
			return word;
		}else if(word.length() == 1 && "+-*/".indexOf(word)>=0){
			return word;
		}
		
		String result = word;
		word = word.toLowerCase();
		switch (word) {
		case "zero":
			result = "0";
			break;
		case "null":
			result = "0";
			break;
		case "one":
			result = "1";
			break;
		case "two":
			result = "2";
			break;
		case "three":
			result = "3";
			break;
		case "four":
			result = "4";
			break;
		case "five":
			result = "5";
			break;
		case "six":
			result = "6";
			break;
		case "seven":
			result = "7";
			break;
		case "eight":
			result = "8";
			break;
		case "nine":
			result = "9";
			break;
		case "plus":
			result = "+";
			break;
		case "minus":
			result = "-";
			break;
		case "multiply":
			result = "*";
			break;
		case "times":
			result = "*";
			break;
		case "x":
			result = "*";
			break;
		case "equals":
			result = "";
			break;
		default:
			result = "";
			break;
		}
		return result;
	}
}

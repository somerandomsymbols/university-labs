package main;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.EnumMap;
import java.util.HashMap;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;


public class Tokenizer
{
	/*public static final String tab = "    ";
	public static final String decimal_regex = "[\\+\\-]?\\d+(\\.\\d+)?";
	public static final String int_regex = "[\\+\\-]?\\d+";
	public static final String hex_regex = "[\\+\\-]?0x\\[A-Fa-f0-9]+";
	public static final String string_regex = "[\'][^\']*[\']|[\"][^\"]*[\"]";
	public static final String comment_regex = "#.*";*/
	public static final String keywords_regex = "nonlocal|continue"
			+ "|finally"
			+ "|global|except|lambda|import|assert|return"
			+ "|False|raise|while|yield|class|break"
			+ "|None|True|elif|else|with|from|pass"
			+ "|and|try|not|for|del|def"
			+ "|or|as|if|in|is";
	/*public static final String operator_regex = "\\+\\+|\\-\\-"
			+ "|\\>|\\>\\=|\\<|\\<\\=|\\=\\=|\\!\\="
			+ "|\\+\\=|\\-\\=|\\*\\=|/\\=|//\\=|%\\=|\\*\\*\\="
			+ "|&\\=|\\|\\=|\\^\\=|\\>\\>\\=|\\<\\<\\="
			+ "|&|\\||~|\\^|\\>\\>|\\<\\<"
			+ "|\\+|\\-|\\*|/|//|%|\\*\\*|\\=";
	public static final String separator_regex = tab + "|\\(|\\)|,|\\.|\\[|\\]|\\{|\\}|:|;";
	public static final String identifier_regex = "[a-zA-z_]\\w*";*/
	EnumMap<TokenClass, String> class_regex = new EnumMap<>(TokenClass.class);
	HashMap<TokenClass, FSM> class_fsm = new HashMap<TokenClass, FSM>();
	
	public Tokenizer()
	{
		//class_regex.put(TokenClass.SEPARATOR, separator_regex);
		//class_regex.put(TokenClass.DECIMAL, decimal_regex);
		//class_regex.put(TokenClass.STRING, string_regex);
		//class_regex.put(TokenClass.HEX, hex_regex);
		//class_regex.put(TokenClass.COMMENT, comment_regex);
		class_regex.put(TokenClass.KEYWORD, keywords_regex);
		//class_regex.put(TokenClass.OPERATOR, operator_regex);
		//class_regex.put(TokenClass.IDENTIFIER, identifier_regex);
		
		String chars = " _~!?`+-*<>&|^%/=()[]{}.,:;\\#@$";
		String letters = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
		String digits = "1234567890";
		
		FSM decimal_fsm = new FSM(0);
		decimal_fsm.F.add(1);
		decimal_fsm.F.add(3);
		decimal_fsm.put(0, digits, 3);
		decimal_fsm.put(0, "+-", 4);
		decimal_fsm.put(0, '.', 5);
		
		decimal_fsm.put(1, digits, 1);
		decimal_fsm.put(1, "+-.", 5);
		
		decimal_fsm.put(2, digits, 1);
		decimal_fsm.put(2, "+-.", 5);
		
		decimal_fsm.put(3, '.', 2);
		decimal_fsm.put(3, digits, 3);
		decimal_fsm.put(3, "+-", 5);
		
		decimal_fsm.put(4, digits, 3);
		decimal_fsm.put(4, "+-.", 5);
		
		decimal_fsm.put(5, digits, 5);
		decimal_fsm.put(5, "+-.", 5);
		
		class_fsm.put(TokenClass.DECIMAL, decimal_fsm);
		
		FSM string_fsm = new FSM(0);
		string_fsm.F.add(2);
		string_fsm.put(0, '\"', 1);
		string_fsm.put(0, '\'', 3);
		
		string_fsm.put(1, digits, 1);
		string_fsm.put(1, letters, 1);
		string_fsm.put(1, chars, 1);
		string_fsm.put(1, '\'', 1);
		string_fsm.put(1, '\"', 2);
		
		string_fsm.put(3, '\'', 2);
		string_fsm.put(3, digits, 3);
		string_fsm.put(3, letters, 3);
		string_fsm.put(3, chars, 3);
		string_fsm.put(3, '\"', 3);
		
		class_fsm.put(TokenClass.STRING, string_fsm);
		
		FSM identifier_fsm = new FSM(0);
		identifier_fsm.F.add(1);
		identifier_fsm.put(0, letters, 1);
		identifier_fsm.put(0, '_', 1);
		
		identifier_fsm.put(1, letters, 1);
		identifier_fsm.put(1, digits, 1);
		identifier_fsm.put(1, '_', 1);
		
		class_fsm.put(TokenClass.IDENTIFIER, identifier_fsm);
		
		FSM separator_fsm = new FSM(0);
		separator_fsm.F.add(1);
		separator_fsm.put(0, "()[]{}.,:;", 1);
		separator_fsm.put(0, ' ', 4);
		
		separator_fsm.put(2, ' ', 1);
		
		separator_fsm.put(3, ' ', 2);
		
		separator_fsm.put(4, ' ', 3);
		
		class_fsm.put(TokenClass.SEPARATOR, separator_fsm);
		
		FSM operator_fsm = new FSM(0);
		operator_fsm.F.add(1);
		operator_fsm.F.add(3);
		operator_fsm.F.add(4);
		operator_fsm.F.add(6);
		operator_fsm.F.add(7);
		operator_fsm.F.add(8);
		operator_fsm.F.add(9);
		operator_fsm.put(0, "~", 1);
		operator_fsm.put(0, "!", 2);
		operator_fsm.put(0, "<>&|^%=", 3);
		operator_fsm.put(0, '+', 4);
		operator_fsm.put(0, '-', 5);
		operator_fsm.put(0, '*', 6);
		operator_fsm.put(0, '/', 8);
		
		operator_fsm.put(2, '=', 1);
		
		operator_fsm.put(3, '=', 1);
		
		operator_fsm.put(4, "+=", 1);
		operator_fsm.put(5, "-=", 1);
		
		operator_fsm.put(6, '=', 1);
		operator_fsm.put(6, '*', 7);
		operator_fsm.put(7, '=', 1);
		
		operator_fsm.put(8, '=', 1);
		operator_fsm.put(8, '/', 9);
		operator_fsm.put(9, '=', 1);
		
		class_fsm.put(TokenClass.OPERATOR, operator_fsm);
		
		FSM comment_fsm = new FSM(0);
		comment_fsm.F.add(1);
		comment_fsm.put(0, '#', 1);
		comment_fsm.put(1, digits, 1);
		comment_fsm.put(1, letters, 1);
		comment_fsm.put(1, chars, 1);
		comment_fsm.put(1, "\'\"", 1);
		
		class_fsm.put(TokenClass.COMMENT, comment_fsm);
		
		FSM hex_fsm = new FSM(0);
		hex_fsm.F.add(1);
		hex_fsm.put(0, '0', 3);
		hex_fsm.put(0, "+-", 4);
		
		hex_fsm.put(1, "ABCDEFabcdef", 1);
		hex_fsm.put(1, digits, 1);
		
		hex_fsm.put(2, "ABCDEFabcdef", 1);
		hex_fsm.put(2, digits, 1);
		
		hex_fsm.put(3, 'x', 2);
		
		hex_fsm.put(4, '0', 3);
		
		class_fsm.put(TokenClass.HEX, hex_fsm);
	}
	
	public int Find(TokenClass c, String s)
	{
		if (c == TokenClass.KEYWORD)
		{
			Pattern p = Pattern.compile("^(" + class_regex.get(c) + ")");
			Matcher m = p.matcher(s);
			
			if (m.find())
				return m.end();
			else
				return 0;
		}
		else
		{
			ArrayList<Integer> chars = new ArrayList<Integer>();
			//System.out.print(s);
			//System.out.println(" :");
			for (char i : s.toCharArray())
			{
				/*

				letter -"l"
				digit -"d"

				*/
				//if ('0' <= i && i <= '9')
					//chars.add(-'d');
				//else if (('a' <= i && i <= 'z') || ('A' <= i && i <= 'Z'))
					//chars.add(-'l');
				//else
					chars.add(0+i);
				//System.out.print(chars.get(chars.size()-1));
				//System.out.print(" ");
			}
			//System.out.println();
			FSM fsm = class_fsm.get(c);
			int res = fsm.Read(chars);
			//System.out.println(res);
			return res;
		}
	}
	
	public ArrayList<Token> parse(String s)
	{
		ArrayList<Token> tokens = new ArrayList<Token>();
		
		boolean f = true;
		
		while (f)
		{
			f = false;
			
			if (!s.isEmpty())
			{
				for (TokenClass e : TokenClass.values())
				{
					if (s.isEmpty())
						break;
					
					int m = Find(e, s);
					
					if (m > 0)
					{
						f = true;
						tokens.add(new Token(e, s.substring(0,m)));
						s = s.substring(m);
						break;
					}
				}
				
				if (!f && s.startsWith(" "))
				{
					s = s.trim();
					f = true;
				}
			}
		}
		
		if (!s.isEmpty())
		{
			System.out.println("Error while parsing expression: " + s);
		}
		
		return tokens;
	}
}

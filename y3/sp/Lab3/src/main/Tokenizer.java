package main;

import java.util.ArrayList;
import java.util.EnumMap;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;


public class Tokenizer
{
	public static final String tab = "    ";
	public static final String decimal_regex = "[\\+\\-]?\\d+(\\.\\d+)?";
	//public static final String int_regex = "[\\+\\-]?\\d+";
	public static final String hex_regex = "[\\+\\-]?0x\\[A-Fa-f0-9]+";
	public static final String string_regex = "[\'][^\']*[\']|[\"][^\"]*[\"]";
	public static final String comment_regex = "#.*";
	public static final String keywords_regex = "nonlocal|continue"
			+ "|finally"
			+ "|global|except|lambda|import|assert|return"
			+ "|False|raise|while|yield|class|break"
			+ "|None|True|elif|else|with|from|pass"
			+ "|and|try|not|for|del|def"
			+ "|or|as|if|in|is";
	public static final String operator_regex = "\\+\\+|\\-\\-"
			+ "|\\>|\\>\\=|\\<|\\<\\=|\\=\\=|\\!\\="
			+ "|\\+\\=|\\-\\=|\\*\\=|/\\=|//\\=|%\\=|\\*\\*\\="
			+ "|&\\=|\\|\\=|\\^\\=|\\>\\>\\=|\\<\\<\\="
			+ "|&|\\||~|\\^|\\>\\>|\\<\\<"
			+ "|\\+|\\-|\\*|/|//|%|\\*\\*|\\=";
	public static final String separator_regex = tab + "|\\(|\\)|,|\\.|\\[|\\]|\\{|\\}|:|;";
	public static final String identifier_regex = "[a-zA-z_]\\w*";
	EnumMap<TokenClass, String> class_regex = new EnumMap<>(TokenClass.class);
	
	public Tokenizer()
	{
		class_regex.put(TokenClass.SEPARATOR, separator_regex);
		class_regex.put(TokenClass.DECIMAL, decimal_regex);
		class_regex.put(TokenClass.HEX, hex_regex);
		class_regex.put(TokenClass.STRING, string_regex);
		class_regex.put(TokenClass.COMMENT, comment_regex);
		class_regex.put(TokenClass.KEYWORD, keywords_regex);
		class_regex.put(TokenClass.OPERATOR, operator_regex);
		class_regex.put(TokenClass.IDENTIFIER, identifier_regex);
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
				for (Map.Entry<TokenClass, String> e : class_regex.entrySet())
				{
					if (s.isEmpty())
						break;
					
					Pattern p = Pattern.compile("^(" + e.getValue() + ")");
					Matcher m = p.matcher(s);
					
					if (m.find())
					{
						f = true;
						tokens.add(new Token(e.getKey(), m.group()));
						s = s.substring(m.end());
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

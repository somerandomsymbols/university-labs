package main;

enum TokenClass{
	KEYWORD,
	COMMENT,
	STRING,
	HEX,
	DECIMAL,
    OPERATOR,
    SEPARATOR,
    IDENTIFIER
}

public class Token
{
	public TokenClass type;
	public String value;
	
	public Token(TokenClass t, String v)
	{
		type = t;
		value = v;
	}
}

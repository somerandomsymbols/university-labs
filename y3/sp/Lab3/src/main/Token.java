package main;

enum TokenClass{
	COMMENT,
	STRING,
	DECIMAL,
	HEX,
    KEYWORD,
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

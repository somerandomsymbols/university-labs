package main;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Main
{
	public static final String tab = "	";

	public static void main(String[] args)
	{
		ArrayList<String> lines = new ArrayList<String>();
		
		try
		{
			//String filepath = "program.py";
			System.out.print("Filepath: ");
			Scanner in = new Scanner(System.in);
			String filepath = in.nextLine();
			File file = new File(filepath);
			Scanner reader = new Scanner(file);
			
			while (reader.hasNextLine())
			{
				lines.add(reader.nextLine());
			}
			
			lines.removeIf((x)->x.isEmpty());
		}
		catch (FileNotFoundException e)
		{
			e.printStackTrace();
		}
		
		ArrayList<Token> tokens = new ArrayList<Token>();
		Tokenizer tokenizer = new Tokenizer();
		
		for (String s : lines)
		{
			tokens.addAll(tokenizer.parse(s));
		}
		
		for (Token t : tokens)
		{
			if (t.type != TokenClass.COMMENT)
				System.out.println("<" + t.value + "> - <" + t.type + ">");
		}
	}

}

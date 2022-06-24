package cyb.ttp.lab1;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class FileOpener {
	private Scanner reader;
	final String s = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
	
	public boolean isOpen()
	{
		return reader == null;
	}
	
	public boolean openFile(String filepath)
	{
		try
		{
			File file = new File(filepath);
			reader = new Scanner(file);
			return true;
		}
		catch (FileNotFoundException e)
		{
			System.out.println("An error occurred.");
			e.printStackTrace();
			return false;
		}
	}
	
	public void closeFile()
	{
		if (reader != null)
		{
			reader.close();
			reader = null;
		}
	}
	
	public ArrayList<String> getWords()
	{
		ArrayList<String> words = new ArrayList<String>();
		
		while (reader.hasNextLine()) 
		{
			String line = reader.nextLine();
			
			for (int i = 0; i < line.length(); ++i)
			{
				String word = "";
				
				while (i < line.length() && WordsComparator.contains(s, line.charAt(i)))
				{
					word = word + line.charAt(i);
					++i;
				}
				
				if (word.length() > 30)
					word = word.substring(0, 30);
				
				if (!word.isEmpty())
					words.add(word);
			}
		}
		
		return words;
	}
}

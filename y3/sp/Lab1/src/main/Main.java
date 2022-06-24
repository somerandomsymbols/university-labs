package main;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class Main
{
	public static void main(String[] args)
	{
		String s = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
		Set<String> words = new HashSet<String>();
		BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
	    String filepath = "file.txt";
		try {
			System.out.print("File path: ");
			filepath = input.readLine();
		} catch (IOException e1) {
			System.out.println("An error occurred.");
			e1.printStackTrace();
		}
		//String filepath = "D:\\Games\\Riot Games\\League of Legends\\debug.log";
		
		try
		{
			File file = new File(filepath);
			Scanner reader = new Scanner(file);
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
			
			reader.close();

			ArrayList<String> wordsArray = new ArrayList<String>();
			wordsArray.addAll(words);
			
			Comparator<String> comp = new WordsComparator();
			wordsArray.sort(comp);
			
	        for(Object w : wordsArray.toArray())
	        	System.out.println(w);
		} 
		catch (FileNotFoundException e)
		{
			System.out.println("An error occurred.");
			e.printStackTrace();
		}

	}

}

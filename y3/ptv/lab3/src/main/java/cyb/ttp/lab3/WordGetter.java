package cyb.ttp.lab3;

import java.io.FileNotFoundException;
import java.util.ArrayList;

public class WordGetter {
	public DataAccessService dataAccess;
	private final String alphabet = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
	
	public void setDataAccess(DataAccessService das)
	{
		this.dataAccess = das;
	}
	
	public boolean openFile(String filepath) throws FileNotFoundException
	{
		this.dataAccess.openFile(filepath);
		return true;
	}
	
	public ArrayList<String> getWords()
	{
		ArrayList<String> words = new ArrayList<String>();
		WordsComparator wc = new WordsComparator();
		
		while (dataAccess.hasNextLine()) 
		{
			String line = dataAccess.nextLine();
			
			for (int i = 0; i < line.length(); ++i)
			{
				String word = "";
				
				while (i < line.length() && wc.contains(alphabet, line.charAt(i)))
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
	
	public void closeFile()
	{
		this.dataAccess.closeFile();
	}
}

package cyb.ttp.lab3;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class FileOpener implements DataAccessService{
	private Scanner reader;
	
	public boolean isOpen()
	{
		return reader != null;
	}
	
	public boolean openFile(String filepath) throws FileNotFoundException
	{
		File file = new File(filepath);
		reader = new Scanner(file);
		return true;
	}
	
	public void closeFile()
	{
		if (reader != null)
		{
			reader.close();
			reader = null;
		}
	}

	public boolean hasNextLine() {
		return reader.hasNextLine();
	}

	public String nextLine() {
		return reader.nextLine();
	}
}

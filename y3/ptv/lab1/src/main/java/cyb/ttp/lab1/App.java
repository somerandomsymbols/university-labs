package cyb.ttp.lab1;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

/**
 * Hello world!
 *
 */
public class App 
{
    public static void main( String[] args )
    {
    	BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
	    String filepath = "file.txt";
	    
		try {
			System.out.print("File path: ");
			filepath = input.readLine();
		} catch (IOException e1) {
			System.out.println("An error occurred.");
			e1.printStackTrace();
		}
		
		FileOpener opener = new FileOpener();
		opener.openFile(filepath);
		Set<String> wordsset = new HashSet<String>();
		wordsset.addAll(opener.getWords());
		opener.closeFile();
		
		ArrayList<String> words = new ArrayList<String>();
		words.addAll(wordsset);
		words.sort(new WordsComparator());
		
        for(Object w : words)
        	System.out.println(w);
    }
}

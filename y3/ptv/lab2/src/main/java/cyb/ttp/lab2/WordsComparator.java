package cyb.ttp.lab2;

import java.util.Comparator;

public class WordsComparator implements Comparator<String>
{
	public static boolean contains(String s, char c)
	{
		return s.lastIndexOf(c) >= 0;
	}
	
	public int compare(String a, String b)
	{
		String vow = "EUIOAeuioa";
		int an = 0, bn = 0;
	    
		for (int i = 0; i < a.length(); ++i)
	    	if (contains(vow, a.charAt(i)))
	    		an++;
	    for (int i = 0; i < b.length(); ++i)
	    	if (contains(vow, b.charAt(i)))
	    		bn++;
	    
	    double aq = an, bq = bn;
	    aq /= a.length();
	    bq /= b.length();
	    		
	    return Double.compare(aq, bq);
	}
}

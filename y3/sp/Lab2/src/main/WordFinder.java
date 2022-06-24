package main;

public class WordFinder
{
	FSM fsm;
	
	public WordFinder (FSM x)
	{
		fsm = x;
	}
	
	public void PrintWords()
	{
		PrintWords("", fsm.S);
	}
	
	private void PrintWords(String s, int d)
	{
		if (fsm.Read(s))
			System.out.println(s);
		
		if (d > 0)
			for (int i = 0; i < fsm.A; ++i)
				PrintWords(s + String.valueOf((char) (i + 'a')), d-1);
	}
}

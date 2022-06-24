package main;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Scanner;

public class MyLang
{
	private String axiom;
	private HashSet<String> terminals;
	private HashSet<String> non_terminals;
	private HashSet<Node> rules;
	
	public MyLang()
	{
		this.axiom = "";
		this.terminals = new HashSet<String>();
		this.non_terminals = new HashSet<String>();
		this.rules = new HashSet<Node>();
	}
	
	public HashSet<String> getTerminals()
	{
		return new HashSet<String>(this.terminals);
	}
	
	public HashSet<String> getNonTerminals()
	{
		return new HashSet<String>(this.non_terminals);
	}
	
	public void AddSymbol(String s)
	{
		if (s.isEmpty())
			return;
		
		if (s.length() > 2 && s.charAt(0) == '#' && s.charAt(s.length()-1) == '#')
			this.non_terminals.add(s);
		else
			this.terminals.add(s);
	}
	
	public void AddSymbols(ArrayList<String> a)
	{
		for (String s : a)
			this.AddSymbol(s);
	}
	
	/*public boolean Read(String filepath)
	{
		this.axiom = "";
		this.terminals.clear();
		this.non_terminals.clear();
		this.rules.clear();
		File file;
		Scanner reader;
		
		try
		{
			file = new File(filepath);
			reader = new Scanner(file);
		}
		catch (FileNotFoundException e)
		{
			return false;
		}
		
		String A;
		
		if (reader.hasNextLine())
		{
			A = reader.nextLine();
		}
		else
		{
			reader.close();
			return false;
		}
		
		String L = "";
		
		while (reader.hasNextLine())
		{
			ArrayList<String> symbols = new ArrayList<String>(Arrays.asList(reader.nextLine().trim().split(" ")));
			symbols.removeIf((x) -> x.isEmpty());
			ArrayList<String> words = new ArrayList<String>();

			int flag = -1;
			for (int s = 0; s < symbols.size(); ++s)
			{
				if (flag == -1 && symbols.get(s).charAt(0) == '#')
				{
					flag = s;
				}
				else if (flag == -1 && symbols.get(s).charAt(0) != '#')
				{
					words.add(symbols.get(s));
				}
				else if (flag != -1 && symbols.get(s).charAt(symbols.get(s).length()-1) == '#')
				{
					String w = "";
					
					for (int i = flag; i <= s; ++i)
						w = w + symbols.get(i);
					
					flag = -1;
					words.add(w);
				}
			}
			
			for (String w : words.subList(1, words.size()))
				this.AddSymbol(w);
			
			if (L.isEmpty() && words.get(0).equals("!"))
			{
				reader.close();
				return false;
			}
			
			if (!words.get(0).equals("!"))
			{
				L = words.get(0);
				this.AddSymbol(L);
			}
			
			this.rules.add(new Rule(L, words.subList(1, words.size())));
		}
		
		this.axiom = A;
		reader.close();
		return true;
	}*/
	
	public boolean Read(String filepath)
	{
		this.axiom = "";
		this.terminals.clear();
		this.non_terminals.clear();
		this.rules.clear();
		File file;
		Scanner reader;
		
		try
		{
			file = new File(filepath);
			reader = new Scanner(file);
		}
		catch (FileNotFoundException e)
		{
			return false;
		}
			
		String A;
		
		if (reader.hasNextLine())
		{
			A = reader.nextLine();
			
			if (A.contains(" "))
			{
				reader.close();
				return false;
			}
		}
		else
		{
			reader.close();
			return false;
		}
		
		String L = "";
		
		while (reader.hasNextLine())
		{
			ArrayList<String> words = new ArrayList<String>(Arrays.asList(reader.nextLine().trim().split(" ")));
			words.removeIf((x) -> x.isEmpty());
			
			for (String w : words.subList(1, words.size()))
				this.AddSymbol(w);
			
			if (L.isEmpty() && words.get(0).equals("!"))
			{
				reader.close();
				return false;
			}
			
			if (!words.get(0).equals("!"))
			{
				L = words.get(0);
				this.AddSymbol(L);
			}
			
			this.rules.add(new Node(L, words.subList(1, words.size())));
		}
		
		this.axiom = A;
		reader.close();
		return true;
	}
	
	public String toString()
	{
		if (this.isNull())
			return "{0}";
		
		String N = "";
		
		for (String n : this.non_terminals)
			N = N + " " + n;
		
		String T = "";
		
		for (String t : this.terminals)
			T = T + " " + t;
		
		String P = "\n";
		
		for (Node r : rules)
			P = P + r.toString() + "\n";
		
		return String.format("{ N = {%s}, T = {%s}, P:%sS = %s }", N.substring(1), T.substring(1), P, this.axiom);
	}
	
	public boolean isNull()
	{
		return this.axiom.isEmpty() || this.rules.isEmpty() || this.terminals.isEmpty() || this.non_terminals.isEmpty();
	}
	
	public HashSet<String> getProductiveNonTerminals()
	{
		HashSet<String> productive = new HashSet<String>();
		HashSet<String> productive_next = new HashSet<String>();
		HashSet<String> term = new HashSet<String>(this.terminals);
		
		do
		{
			term.addAll(productive_next);
			productive.addAll(productive_next);
			
			for (Node r : this.rules)
				if (term.containsAll(r.getRight()))
					productive_next.add(r.getLeft());
		}
		while(!productive.equals(productive_next));
		
		return productive;
	}
	
	public HashSet<String> getReachableSymbols()
	{
		HashSet<String> reachable = new HashSet<String>();
		reachable.add(this.axiom);
		HashSet<String> reachable_next = new HashSet<String>();
		reachable_next.add(this.axiom);
		
		do
		{
			reachable.addAll(reachable_next);
			
			for (Node r : this.rules)
				reachable_next.addAll(r.getRight());
		}
		while (!reachable.equals(reachable_next));
		
		return reachable;
	}
	
	public HashSet<String> getSignificantSymbols()
	{
		HashSet<String> productive = this.getProductiveNonTerminals();
		productive.addAll(this.terminals);	
		HashSet<String> significant = new HashSet<String>();
		
		if (!productive.contains(this.axiom))
			return significant;
		
		significant.add(this.axiom);
		HashSet<String> significant_next = new HashSet<String>();
		significant_next.add(this.axiom);
		
		do
		{
			significant.addAll(significant_next);
			
			for (Node r : this.rules)
				if (productive.contains(r.getLeft()) && productive.containsAll(r.getRight()))
					significant_next.addAll(r.getRight());
		}
		while (!significant.equals(significant_next));
		
		return significant;
	}
	
	public boolean isEmpty()
	{
		if (this.isNull())
			return true;
		
		return !this.getProductiveNonTerminals().contains(this.axiom);
	}
	
	public MyLang getSignificantGrammar()
	{
		MyLang g = new MyLang();
		HashSet<String> significant = this.getSignificantSymbols();
		g.axiom = this.axiom;
		
		for (Node r : this.rules)
			if (significant.contains(r.getLeft()) && significant.containsAll(r.getRight()))
			{
				g.rules.add(r);
				g.AddSymbol(r.getLeft());
				g.AddSymbols(r.getRight());
			}
		
		return g;
	}
}

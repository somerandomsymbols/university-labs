package main;

import java.util.AbstractMap;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class FSM {
	public int s0;
	public ArrayList<Integer> F;
	public Map<AbstractMap.SimpleEntry<Integer, Integer>, Integer> f = new HashMap<AbstractMap.SimpleEntry<Integer, Integer>, Integer>();
	
	public FSM(int x)
	{
		s0 = x;
		F = new ArrayList<Integer>();
	}
	
	public static AbstractMap.SimpleEntry<Integer, Integer> p(int x, int y)
	{
		return new AbstractMap.SimpleEntry<Integer, Integer>(x, y);
	}
	
	public void put(int x, String y, int z)
	{
		for (char c : y.toCharArray())
			f.put(p(x,c), z);
	}
	
	public void put(int x, int y, int z)
	{
		f.put(p(x,y), z);
	}
	
	public int Read(ArrayList<Integer> x)
	{
		int st = s0;
		int lmax = 0;
		
		for (int i = 0; i < x.size(); ++i)
		{
			AbstractMap.SimpleEntry<Integer, Integer> pair = p(st, x.get(i));
			
			if (f.containsKey(pair))
				st = f.get(pair);
			else
				st = -1;
			
			if (F.contains(st))
				lmax = i+1;
		}
		
		return lmax;
	}
}

package main;

import java.util.ArrayList;
import java.util.Arrays;

public class FSM {
	public int S, s0;
	public int A;
	public ArrayList<Integer> F;
	public int[][] f;
	
	public FSM(int x, int y, int z)
	{
		S = x;
		s0 = y;
		A = z;
		F = new ArrayList<Integer>();
		f = new int[S][A];
		
		for (int[] i : f)
			Arrays.fill(i, -1);
	}
	
	public boolean Read(String x)
	{
		int st = s0;
		
		for (char c : x.toCharArray())
		{
			if (c - 'a' >= A || f[st][c - 'a'] == -1)
				return false;
			else
				st = f[st][c - 'a'];
		}
		
		return F.contains(st);
	}
}

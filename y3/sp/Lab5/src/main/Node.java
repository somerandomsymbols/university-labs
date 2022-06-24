package main;

import java.util.ArrayList;
import java.util.List;

public class Node
{
	private String left;
	private ArrayList<String> right;
	
	public Node(String l, List<String> r)
	{
		left = l;
		right = new ArrayList<String>(r);
	}
	
	public String getLeft()
	{
		return left;
	}
	
	public ArrayList<String> getRight()
	{
		return right;
	}
	
	public String toString()
	{
		if (right.isEmpty())
			return left + " ::= ";
		
		String R = "";
		
		for (String r : right)
			R = R + " " + r;
		
		return left + " ::= " + R.substring(1);
	}
}
 
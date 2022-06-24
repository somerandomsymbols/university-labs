package main;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {
	
	
	
    public static void main(String []args)
    {		
		try
		{
			System.out.println("(a+b)(a+c)(b+c)a*");
			String filepath = "file.txt";
			File file = new File(filepath);
			Scanner reader = new Scanner(file);
			int A = Integer.parseInt(reader.nextLine());
			int S = Integer.parseInt(reader.nextLine());
			int s0 = Integer.parseInt(reader.nextLine());
			FSM fsm = new FSM(S,s0,A);
			int Fnum = Integer.parseInt(reader.nextLine());	
			
			for (int i = 0; i < Fnum; ++i)
				fsm.F.add(
						Integer.parseInt(
								reader.nextLine()));
			
			while (reader.hasNextLine())
			{
				String line = reader.nextLine();
				String[] nums = line.split(" ");
				int s1 = Integer.parseInt(nums[0]);
				char a = nums[1].charAt(0);
				int s2 = Integer.parseInt(nums[2]);
				fsm.f[s1][a - 'a'] = s2;
			}
			
			reader.close();
			WordFinder wf = new WordFinder(fsm);
			wf.PrintWords();
		} 
		catch (FileNotFoundException e)
		{
			System.out.println("An error occurred.");
			e.printStackTrace();
		}
    }
}


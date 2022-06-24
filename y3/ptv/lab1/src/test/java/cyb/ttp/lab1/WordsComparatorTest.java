package cyb.ttp.lab1;

import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized.Parameters;
import org.junit.runners.Parameterized;

import java.util.Arrays;
import java.util.Collection;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.*;

@RunWith(Parameterized.class)
public class WordsComparatorTest
{
	private WordsComparator comparator;
	private String word1, word2;
	private int result;
	
	public WordsComparatorTest(String a, String b, int r)
	{
		word1 = a;
		word2 = b;
		result = r;
	}
	
	@Parameters
	public static Collection testData() {
	      return Arrays.asList(new Object[][] {
	         { "a", "b", 1 },
	         { "ab", "aa", -1 },
	         { "ab", "ba", 0 }
	      });
	   }
	
	
	@BeforeClass
	public static void beforeClass()
	{
		
	}
	
	@Before
	public void before()
	{
		comparator = new WordsComparator();
	}
	
	@Test
	public void testContains()
	{
		String v = "aouei";
		String s = "qwrtypsdfghjklzxcvbnm";
		
		for (char c : s.toCharArray())
			assertThat(comparator.contains(v, c), equalTo(false));
		
		for (char c : v.toCharArray())
			assertThat(comparator.contains(v, c), equalTo(true));
	}

	@Test
	public void testCompare()
	{
		assertThat(Integer.signum(comparator.compare(word1, word2)), equalTo(result));
	}
}

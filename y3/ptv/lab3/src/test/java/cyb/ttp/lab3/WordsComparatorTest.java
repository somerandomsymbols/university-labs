package cyb.ttp.lab3;

import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized.Parameters;
import org.mockito.MockitoAnnotations;
import org.mockito.Spy;
import org.junit.runners.Parameterized;

import java.util.Arrays;
import java.util.Collection;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.*;
import static org.mockito.Mockito.*;
import static org.mockito.AdditionalMatchers.*;

@RunWith(Parameterized.class)
public class WordsComparatorTest
{
	@Spy
	private WordsComparator spyDI;
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
		MockitoAnnotations.initMocks(this);
	}

	@Test
	public void test0()
	{
		when(spyDI.contains("a", 'a')).thenReturn(true);
		when(spyDI.contains("a", 'b')).thenReturn(false);
		
		when(spyDI.contains("b", 'a')).thenReturn(false);
		when(spyDI.contains("b", 'b')).thenReturn(true);
		
		when(spyDI.contains("aa", 'a')).thenReturn(true);
		when(spyDI.contains("aa", 'b')).thenReturn(false);
		
		when(spyDI.contains("ab", 'a')).thenReturn(true);
		when(spyDI.contains("ab", 'b')).thenReturn(true);
		
		when(spyDI.contains("ba", 'a')).thenReturn(true);
		when(spyDI.contains("ba", 'b')).thenReturn(true);
		
		assertThat(Integer.signum(spyDI.compare(word1, word2)), equalTo(result));
	}
}

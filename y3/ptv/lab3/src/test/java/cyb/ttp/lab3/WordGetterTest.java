package cyb.ttp.lab3;

import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertTrue;
import static org.mockito.Mockito.*;
import static org.mockito.AdditionalMatchers.*;

import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Collection;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;

@RunWith(Parameterized.class)
public class WordGetterTest {
	private String filepath;
	private Object[] expected;
	private String[] lines;
	private String wrongpath;
	@InjectMocks
	private WordGetter cut;
	@Mock
	private DataAccessService mockedDI;
	
	public WordGetterTest(String f, Object[] e, String[] l)
	{
		super();
		filepath = f;
		expected = e;
		lines = l;
		wrongpath = "wrong" + filepath;
	}
	
	@Parameters
	public static Collection testData() {
	      return Arrays.asList(new Object[][] {
	         { "test1.txt", new Object[] {"wordA", "wordB", "wordC", "wordD", "wordE"}, 
	        	 new String[] {"wordA wordB", "wordC      wordD     ", "", "", "", "wordE"} },
	         { "test2.txt", new Object[]{"lvvvvvvvvvvvwordAvvvvvvvvvvvvl", "lvvvvvvvvvvvwordBvvvvvvvvvvvvl", "lvvvvvvvvvvvwordCvvvvvvvvvvvvl"},
	        	 new String[] {"lvvvvvvvvvvvwordAvvvvvvvvvvvvlooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo", "lvvvvvvvvvvvwordBvvvvvvvvvvvvloooooooooooooooooooooooo lvvvvvvvvvvvwordCvvvvvvvvvvvvloooooooooooooooooooooooooooooooooooooooooooooooo", "", "", "", ""} },
	         { "test3.txt", new Object[]{"wordA", "wordB", "wordC", "wordD"},
	        	 new String[] {"wordA.wordB.. ..wordC///wordD", "", "", "", "", ""} }
	      });
	   }
	
	@Before
	public void before()
	{
		MockitoAnnotations.initMocks(this);
	}
	
	@Test(expected = FileNotFoundException.class)
	public void test0() throws FileNotFoundException
	{
		when(mockedDI.openFile(not(eq(filepath)))).thenThrow(new FileNotFoundException());
		cut.openFile(wrongpath);
	}
	
	@Test
	public void test1() throws FileNotFoundException
	{
		when(mockedDI.isOpen()).thenReturn(true);
		when(mockedDI.hasNextLine()).thenReturn(true, true, true, true, true, true, false);
		when(mockedDI.nextLine()).thenReturn(lines[0], lines[1], lines[2], lines[3], lines[4], lines[5]);
		assertTrue(cut.openFile(filepath));
		assertArrayEquals(expected, cut.getWords().toArray());
		verify(mockedDI, times(lines.length + 1)).hasNextLine();
		verify(mockedDI, times(lines.length)).nextLine();
	}
}

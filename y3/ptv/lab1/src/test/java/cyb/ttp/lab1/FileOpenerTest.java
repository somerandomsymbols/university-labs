package cyb.ttp.lab1;

import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertTrue;

import java.util.Arrays;
import java.util.Collection;
import java.util.List;

import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;

@RunWith(Parameterized.class)
public class FileOpenerTest
{
	private FileOpener opener;
	
	private String filepath;
	private List<Object> expected;

	public FileOpenerTest(String f, List<Object> e)
	{
		super();
		filepath = f;
		expected = e;
	}
	
	@Parameters
	public static Collection testData() {
	      return Arrays.asList(new Object[][] {
	         { "test1.txt", Arrays.asList(new Object[]{"wordA", "wordB", "wordC", "wordD", "wordE"}) },
	         { "test2.txt", Arrays.asList(new Object[]{"lvvvvvvvvvvvwordAvvvvvvvvvvvvl", "lvvvvvvvvvvvwordBvvvvvvvvvvvvl", "lvvvvvvvvvvvwordCvvvvvvvvvvvvl"}) },
	         { "test3.txt", Arrays.asList(new Object[]{"wordA", "wordB", "wordC", "wordD"}) }
	      });
	   }
	
	@BeforeClass
	public static void beforeClass()
	{
		
	}
	
	@Before
	public void before()
	{
		if (opener == null)
			opener = new FileOpener();
		
		if (opener.isOpen())
			opener.closeFile();
	}
	
	@Test
	public void test()
	{
		assertTrue(opener.openFile(filepath));
		assertArrayEquals(expected.toArray(), opener.getWords().toArray());
	}
}

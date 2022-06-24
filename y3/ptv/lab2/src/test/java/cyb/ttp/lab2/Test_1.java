package cyb.ttp.lab2;

import static org.testng.Assert.assertEquals;
import static org.testng.Assert.assertFalse;
import static org.testng.Assert.assertTrue;

import org.testng.annotations.AfterClass;
import org.testng.annotations.AfterMethod;
import org.testng.annotations.AfterSuite;
import org.testng.annotations.AfterTest;
import org.testng.annotations.BeforeClass;
import org.testng.annotations.BeforeMethod;
import org.testng.annotations.BeforeSuite;
import org.testng.annotations.BeforeTest;
import org.testng.annotations.DataProvider;
import org.testng.annotations.Test;

import cyb.ttp.lab2.WordsComparator;

public class Test_1 {
	private WordsComparator comparator;
	
	@DataProvider
	public Object[][] dp()
	{
		return new Object[][] {
			{ "a", "b", 1 },
			{ "ab", "aa", -1 },
			{ "ab", "ba", 0 } };
	}
	
	@Test(groups = {"comparison"})
	public void test_1_0_contains()
	{
		String v = "euioa";
		String s = "qwrtypsdfghjklzxcvbnm";
		String a = "qwertyuiopasdfghjklzxcvbnm";
		
		for (char c : s.toCharArray())
			assertFalse(WordsComparator.contains(v, c));
		
		for (char c : v.toCharArray())
			assertTrue(WordsComparator.contains(v, c));
		
		for (char c : s.toCharArray())
			assertTrue(WordsComparator.contains(a, c));
		
		for (char c : v.toCharArray())
			assertTrue(WordsComparator.contains(a, c));
	}
	
	@Test(dataProvider = "dp", groups = {"comparison", "parametric"})
	public void test_1_0_compare(String word1, String word2, int result)
	{
		assertEquals(Integer.signum(comparator.compare(word1, word2)), result);
	}
	
	@BeforeMethod
	public void beforeMethod() {}
	
	@AfterMethod
	public void afterMethod() {}
	
	@BeforeClass
	public void beforeClass() {
		comparator = new WordsComparator();
	}
	
	@AfterClass
	public void afterClass() {}
	
	@BeforeTest
	public void beforeTest() {}
	
	@AfterTest
	public void afterTest() {}
	
	@BeforeSuite
	public void beforeSuite() {}
	
	@AfterSuite
	public void afterSuite() {}
}

package cyb.ttp.lab2;

import org.testng.annotations.Test;

import cyb.ttp.lab2.FileOpener;

import org.testng.annotations.BeforeMethod;
import org.testng.annotations.AfterMethod;
import org.testng.annotations.DataProvider;
import org.testng.annotations.BeforeClass;

import static org.testng.Assert.assertEquals;
import static org.testng.Assert.assertTrue;

import org.testng.annotations.AfterClass;
import org.testng.annotations.BeforeTest;
import org.testng.annotations.AfterTest;
import org.testng.annotations.BeforeSuite;
import org.testng.annotations.AfterSuite;

public class Test_0
{
	private FileOpener opener;
	
	@DataProvider
	public Object[][] dp()
	{
		return new Object[][] {
			{ "test1.txt", new String[]{"wordA", "wordB", "wordC", "wordD", "wordE"} },
			{ "test2.txt", new String[]{"lvvvvvvvvvvvwordAvvvvvvvvvvvvl", "lvvvvvvvvvvvwordBvvvvvvvvvvvvl", "lvvvvvvvvvvvwordCvvvvvvvvvvvvl"} },
			{ "test3.txt", new String[]{"wordA", "wordB", "wordC", "wordD"} } };
	}
	
	@Test(dataProvider = "dp", groups = {"input", "parametric"})
	public void test_0_0_open(String filepath, String[] expected) {
		assertTrue(opener.openFile(filepath));
		assertEquals(expected, opener.getWords().toArray());
	}
	
	@BeforeMethod
	public void beforeMethod() {
		if (opener == null)
			opener = new FileOpener();
		if (opener.isOpen())
			opener.closeFile();
	}
	
	@AfterMethod
	public void afterMethod() {}
	
	@BeforeClass
	public void beforeClass() {}
	
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

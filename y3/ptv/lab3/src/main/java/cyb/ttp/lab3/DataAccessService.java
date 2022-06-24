package cyb.ttp.lab3;

import java.io.FileNotFoundException;

public interface DataAccessService {
	public boolean isOpen();
	public boolean openFile(String filepath) throws FileNotFoundException;
	public void closeFile();
	public boolean hasNextLine();
	public String nextLine();
}

package IsoSDKJNIPkg;

public class BurnOptions {
	public String volumeLabel = "";
	public String bootImage = "";
	public int writeMethod = -1;
	public boolean jolietFileSystem;
	public boolean bootable;
	public boolean finalize;
	public boolean testBurn;
	public boolean performOPC;
	public boolean verifyAfterBurn;
	public int cacheSize= -1;
	public boolean underrunProtection;
	public boolean ejectAfterBurn;
	public boolean autoErase;
	public boolean rockRidgeFileSystem;
	public boolean padDataTracks;
}

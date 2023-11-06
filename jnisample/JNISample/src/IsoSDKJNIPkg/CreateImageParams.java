package IsoSDKJNIPkg;

public class CreateImageParams {
	//Standard params
	public String impagePath = "";
	public String badSectorsFilePath = "";
	public short imageType = 1;
	public int verifyBufferSectors = 1;
	public boolean fullCapacity = true;
	//REadCorrections
	public boolean errorCorrection = true;
	public boolean blankBadSectors = true;
	public int hardwareRetryCounts = 20;
	public int softwareRetryCounts = 0;
}

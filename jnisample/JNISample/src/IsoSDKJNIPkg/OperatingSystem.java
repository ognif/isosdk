package IsoSDKJNIPkg;
import java.util.Locale;

public class OperatingSystem {
    private static String OS = System.getProperty("os.name", "unknown").toLowerCase(Locale.ROOT);

    public static boolean isWindows()
    {
        return OS.contains("win");
    }

    public static boolean isMac()
    {
        return OS.contains("mac");
    }

    public static boolean isUnix()
    {
        return OS.contains("nux");
    }
    
    public static boolean is64bit()
    {
    	return (System.getProperty("os.arch").indexOf("64") != -1);
    }
}

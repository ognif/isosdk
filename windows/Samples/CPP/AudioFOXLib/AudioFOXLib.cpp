#include "stdafx.h"
#include "AudioFOXLib.h"
#include "AudioFOXLibDlg.h"
#include "config.h"

#define APP_TITLE STR(IsoSDK IsoSDK_VERSION_MAJOR.IsoSDK_VERSION_MINOR Audio FOXToolkit Sample Application)

int RunDataSample()
{
	int argc = 1;
	char *argv[] = {"AudioFOXLib", NULL};

	FXApp application("AudioFOXLib","iFoerster Development");
	
	application.init(argc, argv);

	KAudioFOXLibDlg dlg(&application, APP_TITLE);

	// Create app
	application.create();

	dlg.loadOwner();
	dlg.execute(PLACEMENT_OWNER);

	return 0;
}

#ifdef WIN32

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
#else
int main(int argc, char* argv[])
#endif
{
	return RunDataSample();
}


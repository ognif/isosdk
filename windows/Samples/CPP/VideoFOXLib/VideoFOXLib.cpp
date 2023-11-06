#include "stdafx.h"
#include "VideoFOXLib.h"
#include "VideoFOXLibDlg.h"
#include "config.h"

#define APP_TITLE STR(IsoSDK IsoSDK_VERSION_MAJOR.IsoSDK_VERSION_MINOR Video FOXToolkit Sample Application)

int RunVideoFOXLib()
{
	int argc = 1;
	char *argv[] = {"VideoFOXLib", NULL};

	FXApp application("VideoFOXLib","iFoerster Development");

	application.init(argc, argv);

	KVideoFOXLibDlg dlg(&application, APP_TITLE);

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
{
	return RunVideoFOXLib();
}

#else

int main(int argc, char* argv[])
{
	return RunVideoFOXLib();
}

#endif

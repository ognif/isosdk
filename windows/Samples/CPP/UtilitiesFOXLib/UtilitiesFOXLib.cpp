#include "stdafx.h"
#include "UtilitiesFOXLib.h"
#include "UtilitiesFOXLibDlg.h"
#include "config.h"

#define APP_TITLE STR(IsoSDK IsoSDK_VERSION_MAJOR.IsoSDK_VERSION_MINOR Utilities FOXToolkit Sample Application)

int RunUtilitiesFOXLib()
{
	int argc = 1;
	char *argv[] = {"UtilitiesFOXLib", NULL};

	FXApp application("UtilitiesFOXLib","iFoerster Development");

	application.init(argc, argv);

	KUtilitiesFOXLibDlg dlg(&application, APP_TITLE);

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
	return RunUtilitiesFOXLib();
}


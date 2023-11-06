#include "stdafx.h"
#include "ImageEditFOXLib.h"
#include "ImageEditFOXLibDlg.h"
#include "config.h"
#include <clocale>

#define APP_TITLE STR(IsoSDK IsoSDK_VERSION_MAJOR.IsoSDK_VERSION_MINOR Image Edit FOXToolkit Sample Application)

int RunImageEditFOXLib()
{
	int argc = 1;
	char *argv[] = {"ImageEditFOXLib", NULL};

	FXApp application("ImageEditFOXLib","iFoerster Development");

	application.init(argc, argv);

	KImageEditFOXLibDlg dlg(&application, APP_TITLE);

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
	return RunImageEditFOXLib();
}

#include "stdafx.h"
#include "DataFOXLib.h"
#include "DataFOXLibDlg.h"
#include "config.h"
#include <clocale>

#define APP_TITLE STR(IsoSDK IsoSDK_VERSION_MAJOR.IsoSDK_VERSION_MINOR Data FOXToolkit Sample Application)

int RunDataFOXLib()
{
	int argc = 1;
	char *argv[] = {"DataFOXLib", NULL};

	FXApp application("DataFOXLib","iFoerster Development");

	application.init(argc, argv);

	//application.setNormalFont(new FXFont(&application, "mincho", 14, FXFont::Medium, FXFont::Straight, FONTENCODING_UNICODE));
	//application.setNormalFont(new FXFont(&application, "fixed", 8, FXFont::Medium, FXFont::Straight, FONTENCODING_UNICODE));

	KDataFOXLibDlg dlg(&application, APP_TITLE);

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
	return RunDataFOXLib();
}

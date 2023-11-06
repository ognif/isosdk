#include "stdafx.h"
#include "AboutDlg.h"
#include "config.h"

FXDEFMAP(KAboutDlg) KAboutDlgMap[]= {
	FXMAPFUNC(SEL_COMMAND, FXDialogBox::ID_CANCEL, FXDialogBox::onCmdCancel)
};

FXIMPLEMENT(KAboutDlg, FXDialogBox, KAboutDlgMap, ARRAYNUMBER(KAboutDlgMap))

KAboutDlg::KAboutDlg()
{
}

#define ABOUT_TEXT STR(IsoSDK IsoSDK_VERSION_MAJOR.IsoSDK_VERSION_MINOR Sample Application)

KAboutDlg::KAboutDlg(FXWindow* owner)
	:FXDialogBox(owner, "Information...", DECOR_TITLE|DECOR_BORDER|DECOR_CLOSE, 0, 0, 480, 170)
{
	FXHorizontalFrame* mainFrame = new FXHorizontalFrame(this, LAYOUT_FILL_X|LAYOUT_FILL_Y);
		FXIcon* icon = new FXICOIcon(getApp(), isosdkbig);
		new FXLabel(mainFrame, "", icon);
		FXVerticalFrame* infoFrame = new FXVerticalFrame(mainFrame, LAYOUT_FILL_X|LAYOUT_FILL_Y);
        	new FXLabel(infoFrame, ABOUT_TEXT);
			new FXLabel(infoFrame, IsoSDK_LEGAL_COPYRIGHT);
			new FXHorizontalSeparator(infoFrame);
			new FXLabel(infoFrame, "This example is only for educational purposes. Duplication\nand distribution is prohibited and constitutes a violation of\nthe license agreement", NULL, JUSTIFY_LEFT);
			new FXButton(infoFrame, "OK", NULL, this, FXDialogBox::ID_CANCEL, 
				BUTTON_NORMAL|LAYOUT_RIGHT|LAYOUT_SIDE_RIGHT|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT, 0, 0, 70, 23);

	FXIcon* miniIcon = new FXICOIcon(getApp(), isosdksmall);
	setMiniIcon(miniIcon);
}

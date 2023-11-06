#include "stdafx.h"
#include "SessionDlg.h"
#include "DataFOXLibDlg.h"


FXDEFMAP(KSessionDlg) KSessionDlgMap[] = {
	FXMAPFUNC(SEL_COMMAND,  KSessionDlg::ID_ACCEPT, KSessionDlg::onCmdAccept),
};

FXIMPLEMENT(KSessionDlg, FXDialogBox, KSessionDlgMap, ARRAYNUMBER(KSessionDlgMap))


KSessionDlg::KSessionDlg(FXWindow *owner, const FXString &title)
	: FXDialogBox(owner, title)
	, m_nSession(0)
{
	sessionList = new FXIconList(this, NULL, 0, FRAME_THICK|FRAME_SUNKEN|ICONLIST_DETAILED|ICONLIST_SINGLESELECT|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT, 0, 0, 300, 100);
	sessionList->appendHeader("#", NULL, 30);
	sessionList->appendHeader("Start LBA", NULL, 100);
	sessionList->appendHeader("Size", NULL, 100);

	FXHorizontalFrame *frameButtons = new FXHorizontalFrame(this,  LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X);

	new FXButton(frameButtons, "Cancel", NULL, this, FXDialogBox::ID_CANCEL,
		BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_FIX_WIDTH|LAYOUT_SIDE_RIGHT|LAYOUT_RIGHT|LAYOUT_FIX_HEIGHT,
		0, 0, 70, 25);

	new FXButton(frameButtons, "Ok", NULL, this, ID_ACCEPT,
		BUTTON_DEFAULT|BUTTON_INITIAL|FRAME_RAISED|FRAME_THICK|LAYOUT_FIX_WIDTH|LAYOUT_SIDE_RIGHT|LAYOUT_RIGHT|LAYOUT_FIX_HEIGHT,
		0, 0, 70, 25);


	SMediumInfo infoMedium;
	SSessionInfo infoSession;

	int32 res = GetMediumInformation(BS_CURRENT_DEVICE, &infoMedium);
	handleError(res);

	if (BS_SDK_ERROR_NO == res)
	{
		for (int32 i = 0; i < infoMedium.nLastSession; i++)
		{
			res = ::GetSessionInformation(BS_CURRENT_DEVICE, i+1, &infoSession);
			handleError(res);

			if (BS_SDK_ERROR_NO == res)
			{
				FXString strItem;
				strItem.format("%d\t%d\t%d", i+1, infoSession.dStartLBA, infoSession.dSessionSize);
				sessionList->appendItem(strItem);
			}
		}
	}
}

long KSessionDlg::onCmdAccept(FXObject* sender, FXSelector key, void* data)
{
	m_nSession = sessionList->getCurrentItem() + 1;
	return FXDialogBox::onCmdAccept(sender, key, data);
}

void KSessionDlg::handleError(int32 errCode)
{
	if (errCode != BS_SDK_ERROR_NO)
	{
		getOwner()->handle(this, FXSEL(KDataFOXLibDlg::SEL_ERRORNOTIFY, 0), IntToPvoid(errCode));
	}
}

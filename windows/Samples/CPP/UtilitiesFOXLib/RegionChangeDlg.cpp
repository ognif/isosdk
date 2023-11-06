
#include "stdafx.h"
#include "RegionChangeDlg.h"
#include "UtilitiesFOXLibDlg.h"

FXDEFMAP(KRegionChangeDlg) KRegionChangeMap[]= {
	FXMAPFUNC(SEL_COMMAND, FXDialogBox::ID_ACCEPT, KRegionChangeDlg::onCmdAccept),
	FXMAPFUNC(SEL_COMMAND, FXDialogBox::ID_CANCEL, FXDialogBox::onCmdCancel),
	FXMAPFUNC(SEL_CLOSE, 0, FXDialogBox::onCmdCancel)
};

FXIMPLEMENT(KRegionChangeDlg, FXDialogBox, KRegionChangeMap, ARRAYNUMBER(KRegionChangeMap))

KRegionChangeDlg::KRegionChangeDlg(FXWindow* owner)
	:FXDialogBox(owner, "Set Regional Code")
	,m_nRegion(1)
{
	m_tgtRegion.connect(m_nRegion);

	FXRadioButton* btn1 = new FXRadioButton(this, "1. USA, Canada", &m_tgtRegion, FXDataTarget::ID_OPTION + 1);
	new FXRadioButton(this, "2. West Europe, Japan, South Africa", &m_tgtRegion, FXDataTarget::ID_OPTION + 2);
	new FXRadioButton(this, "3. South East Asia", &m_tgtRegion, FXDataTarget::ID_OPTION + 3);
	new FXRadioButton(this, "4. Australia, Spanish America", &m_tgtRegion, FXDataTarget::ID_OPTION + 4);
	new FXRadioButton(this, "5. Russia, East Europe, Africa", &m_tgtRegion, FXDataTarget::ID_OPTION + 5);
	new FXRadioButton(this, "6. China", &m_tgtRegion, FXDataTarget::ID_OPTION + 6);

	btn1->setCheck(true, true);

	FXHorizontalFrame* btnFrame = new FXHorizontalFrame(this, LAYOUT_FILL_X|LAYOUT_SIDE_RIGHT);
		new FXButton(btnFrame, "Cancel", NULL, this, FXDialogBox::ID_CANCEL,
			BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_FIX_WIDTH|LAYOUT_SIDE_RIGHT|LAYOUT_RIGHT|LAYOUT_FIX_HEIGHT,
			0, 0, 70, 25);
		new FXButton(btnFrame, "OK", NULL, this, ID_ACCEPT,
			BUTTON_DEFAULT|BUTTON_INITIAL|FRAME_RAISED|FRAME_THICK|LAYOUT_FIX_WIDTH|LAYOUT_SIDE_RIGHT|LAYOUT_RIGHT|LAYOUT_FIX_HEIGHT,
			0, 0, 70, 25);
}

KRegionChangeDlg::KRegionChangeDlg()
{	}

KRegionChangeDlg::~KRegionChangeDlg()
{
}

long KRegionChangeDlg::onCmdAccept(FXObject* object,FXSelector sel, void* data)
{
	int32 *res = new int32(::SetRegionalCode(BS_CURRENT_DEVICE, m_nRegion));
	getOwner()->handle(this, FXSEL(FX::SEL_COMMAND, KUtilitiesFOXLibDlg::ID_ERRORNOTIFY), res);

	return FXDialogBox::onCmdAccept(object, sel, data);
}

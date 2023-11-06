#include "stdafx.h"
#include "PropertiesDlg.h"

FXDEFMAP(KPropertiesDlg) KPropertiesMap[]= {0};

FXIMPLEMENT(KPropertiesDlg, FXDialogBox, KPropertiesMap, ARRAYNUMBER(KPropertiesMap))

KPropertiesDlg::KPropertiesDlg(FX::FXApp *app, const Properties &props)
	:FXDialogBox(app, "Properties", DECOR_TITLE|DECOR_BORDER|DECOR_RESIZE, 0, 0, 280, 300)
{
	FXVerticalFrame* frame = new FXVerticalFrame(this, LAYOUT_FILL, 0, 0, 0, 0, 0, 0, 0, 0);

	FXIconList* propsList = new FXIconList(frame, NULL, 0, LAYOUT_FILL|FRAME_THICK|ICONLIST_DETAILED|ICONLIST_EXTENDEDSELECT,
		0, 0, 200, 100);

	propsList->appendHeader("Parameter", NULL, 120);
	propsList->appendHeader("Value", NULL, 140);

	for(size_t i = 0; i < props.size(); ++i)
	{
		propsList->appendItem(props[i].first + "\t" + props[i].second);
	}

	FXHorizontalFrame *frameButtons = new FXHorizontalFrame(frame, LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X);

	new FXButton(frameButtons, "Close", NULL, this, FXDialogBox::ID_CANCEL,
		BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_FIX_WIDTH|LAYOUT_SIDE_RIGHT|LAYOUT_RIGHT|LAYOUT_FIX_HEIGHT,
		0, 0, 70, 25);
}

KPropertiesDlg::KPropertiesDlg()
{
}

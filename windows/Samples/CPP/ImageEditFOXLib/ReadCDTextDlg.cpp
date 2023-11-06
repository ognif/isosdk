#include "stdafx.h"
#include "ReadCDTextDlg.h"

FXDEFMAP(KReadCDTextDlg) KReadCDTextDlgMap[] = {
	FXMAPFUNC(SEL_COMMAND,  KReadCDTextDlg::ID_ACCEPT, KReadCDTextDlg::onCmdAccept)
};

FXIMPLEMENT(KReadCDTextDlg, FXDialogBox, KReadCDTextDlgMap, ARRAYNUMBER(KReadCDTextDlgMap))

KReadCDTextDlg::KReadCDTextDlg(
					FXApp *app, const FXString &title,
					const FXString& strArranger,
					const FXString& strComposer,
					const FXString& strSongWriter,
					const FXString& strPerformer,
					const FXString& strMessage,
					const FXString& strTitle							)
	: FXDialogBox(app, title, DECOR_TITLE|DECOR_CLOSE|DECOR_MENU, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)	
{
	FXVerticalFrame* VFrame = new FXVerticalFrame(this,  LAYOUT_FILL,   0,0,0,0,  10,10,10,0 );
	
	FXMatrix *matrix = new FXMatrix(VFrame, 2, MATRIX_BY_COLUMNS , 0,0,0,0,  10,10,10,10, 10,10  );
		new FXLabel(matrix, "Performer:");
		FXTextField* pTmpTF =
			new FXTextField(matrix, 30, 0, 0, TEXTFIELD_READONLY | FRAME_SUNKEN);
			pTmpTF->setText(strPerformer);
			
		new FXLabel(matrix, "Title:");
		pTmpTF =
			new FXTextField(matrix, 30, 0, 0, TEXTFIELD_READONLY | FRAME_SUNKEN);
			pTmpTF->setText(strTitle);
					
		new FXLabel(matrix, "Arranger:");
		pTmpTF =
			new FXTextField(matrix, 30, 0, 0, TEXTFIELD_READONLY | FRAME_SUNKEN);
			pTmpTF->setText(strArranger);
		
		new FXLabel(matrix, "Composer:");
		pTmpTF =
			new FXTextField(matrix, 30, 0, 0, TEXTFIELD_READONLY | FRAME_SUNKEN);
			pTmpTF->setText(strComposer);
	
		new FXLabel(matrix, "Song Writer:");	
		pTmpTF =
			new FXTextField(matrix, 30, 0, 0, TEXTFIELD_READONLY | FRAME_SUNKEN);
			pTmpTF->setText(strSongWriter);
	
		new FXLabel(matrix, "Message:");	
		pTmpTF =
			new FXTextField(matrix, 30, 0, 0, TEXTFIELD_READONLY | FRAME_SUNKEN);
			pTmpTF->setText(strMessage);

		new FXLabel(matrix, /*filler of a cell*/ "");
		new FXButton(matrix, "Ok", 0, this, ID_ACCEPT,BUTTON_NORMAL | LAYOUT_FIX_WIDTH | LAYOUT_RIGHT ,0,0,70,0);
}

long KReadCDTextDlg::onCmdAccept(FXObject* sender, FXSelector key, void* data)
{
	return FXDialogBox::onCmdAccept(sender, key, data);
}



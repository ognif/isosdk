#ifndef _SECTOR_VIEW_DIALOG_H_
#define _SECTOR_VIEW_DIALOG_H_

#include "fx.h"
#include "Sector2Text.h"
#include <vector>

class KSectorViewDialog : public FXDialogBox
{
	FXDECLARE(KSectorViewDialog)

public:

	enum
	{
		ID_NEXT = FXDialogBox::ID_LAST,
		ID_PREV,
		ID_TEXT_BOX,
		ID_RAW,		
		ID_LBA,		
		ID_LAST
	};

public:
	KSectorViewDialog();
	KSectorViewDialog(FXWindow* owner, int32 nLBA);
	~KSectorViewDialog();

	void create();
	long onLba(FXObject* sender, FXSelector key, void* data);
	long onPrev(FXObject* sender, FXSelector key, void* data);
	long onNext(FXObject* sender, FXSelector key, void* data);

private:

	std::vector< Sector2Text::SectorLines<Sector2Text::IsPrintableTranslator> >
					m_vBuffer;

	int32 m_nCurrentLba;

	FXText		*m_pTextBox;
	FXButton	*m_pNextBtn;
	FXSpinner	*m_pLBASpinner;
	FXButton	*m_pPrevBtn;
	FXDataTarget m_tgtLBA;

	FXint			m_nReadRaw;
	FXDataTarget	m_tgtReadRaw;
	FXCheckButton*	m_pChkReadRaw;
	FXFont*			m_pFont;

	std::vector<KString> readSector(bool bReadRaw, int32 nLBA);
};//class KSectorViewDialog : public FXDialogBox




#endif //_SECTOR_VIEW_DIALOG_H_


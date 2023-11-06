#include "stdafx.h"
#include "SectorViewDialog.h"

#include "FXText.h"

FXDEFMAP(KSectorViewDialog) KSectorViewDialogMap[]= {	
	FXMAPFUNC(SEL_COMMAND,	KSectorViewDialog::ID_PREV,		KSectorViewDialog::onPrev),
	FXMAPFUNC(SEL_COMMAND,	KSectorViewDialog::ID_NEXT,		KSectorViewDialog::onNext),
	FXMAPFUNC(SEL_COMMAND,	KSectorViewDialog::ID_LBA, KSectorViewDialog::onLba),	
	FXMAPFUNC(SEL_COMMAND,	KSectorViewDialog::ID_RAW, KSectorViewDialog::onLba),	
};


FXIMPLEMENT(KSectorViewDialog, FXDialogBox, KSectorViewDialogMap, ARRAYNUMBER(KSectorViewDialogMap))


KSectorViewDialog::KSectorViewDialog() :
	m_nCurrentLba(0)
	,m_nReadRaw(1)
{
}

KSectorViewDialog::KSectorViewDialog(FXWindow* owner, int32 nLBA)
	:FXDialogBox(owner, "Sector View", DECOR_TITLE|DECOR_CLOSE|DECOR_BORDER, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
	,m_nCurrentLba(nLBA)
	,m_nReadRaw(1)
{
	FXVerticalFrame *vFrame = new FXVerticalFrame(this, LAYOUT_FILL|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT, 0, 0, 680, 500);
	
	FXHorizontalFrame *pControlFrame= new FXHorizontalFrame(vFrame, LAYOUT_FILL_X);
		m_pPrevBtn = new FXButton(pControlFrame,"&Previous",0,this,ID_PREV);		
		
		m_pLBASpinner = new FXSpinner(pControlFrame, 5, &m_tgtLBA, FXDataTarget::ID_VALUE,SPIN_NOMAX | FRAME_SUNKEN | FRAME_THICK);

		m_tgtLBA.connect(m_nCurrentLba);
		m_tgtLBA.setTarget(this);
		m_tgtLBA.setSelector(ID_LBA);

		m_pNextBtn = new FXButton(pControlFrame,"&Next",0,this,ID_NEXT);
		
		m_pChkReadRaw = new FXCheckButton(pControlFrame,"Raw",&m_tgtReadRaw, FXDataTarget::ID_VALUE);

		m_tgtReadRaw.connect(m_nReadRaw);
		m_tgtReadRaw.setTarget(this);		
		m_tgtReadRaw.setSelector(ID_RAW);
	
	FXHorizontalFrame *pTextBoxFrame= new FXHorizontalFrame(vFrame, FRAME_NORMAL | FRAME_SUNKEN | LAYOUT_FILL);
		m_pTextBox = new FXText(pTextBoxFrame, this, ID_TEXT_BOX, TEXT_READONLY | LAYOUT_FILL);	
		m_pFont = new FXFont(getApp(), "courier", 6, FXFont::Normal, FXFont::Straight, FONTENCODING_DEFAULT, FXFont::NonExpanded, FXFont::Modern);
		m_pTextBox->setFont(m_pFont);

		FXIcon *isosdkIcon = new FXICOIcon(getApp(), isosdksmall);
		setIcon(isosdkIcon);

}
KSectorViewDialog::~KSectorViewDialog()
{
	delete m_pFont;
}

void KSectorViewDialog::create()
{	
    FXDialogBox::create();
	onLba(0,0,0);
}

long KSectorViewDialog::onPrev(FXObject* sender, FXSelector key, void* data)
{
	if (m_nCurrentLba > 0)
	{
		--m_nCurrentLba;
	}

	return onLba(sender, key, data);
}

long KSectorViewDialog::onNext(FXObject* sender, FXSelector key, void* data)
{
	++m_nCurrentLba;
	return onLba(sender, key, data);
}

long KSectorViewDialog::onLba(FXObject* sender, FXSelector key, void* data)
{
	std::vector<KString> stringsLines = readSector(m_nReadRaw != 0, m_nCurrentLba);	
	m_pTextBox->setText("");

	for(size_t i = 0; i < stringsLines.size(); ++i)
	{
		m_pTextBox->appendText(SDK2FoxString( (const wchar_t*)stringsLines[i] ) + '\n' );
	}

	return 1;
}

std::vector<KString> KSectorViewDialog::readSector(bool bReadRaw, int32 nLBA)
{
	int32 buff_length = bReadRaw ? 2352 : 2048;
	int8 nFormat = bReadRaw ? BS_IMG_BIN : BS_IMG_ISO;

	uint8 *buff = new uint8[buff_length];
	/*int32 nRes = */::ReadSectors(BS_READ_DEVICE, m_nCurrentLba, 1, nFormat, buff, buff_length);

	m_vBuffer.resize(1);
	m_vBuffer[0].setData(buff, buff_length);
	delete[] buff;
	return m_vBuffer[0].getLines();		
}

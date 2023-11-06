#ifndef REGIONCHANGEDLG_H
#define REGIONCHANGEDLG_H

class KRegionChangeDlg: public FXDialogBox
{
	FXDECLARE(KRegionChangeDlg)

public:

	enum
	{
		ID_LAST = FXDialogBox::ID_LAST
	};

public:
	KRegionChangeDlg(FXWindow* owner);
	~KRegionChangeDlg();

	long onCmdAccept(FXObject*,FXSelector,void*);

private:
	KRegionChangeDlg();

	FXint m_nRegion;
	FXDataTarget m_tgtRegion;
};

#endif

#ifndef _KCDTIMERULE_H_
#define _KCDTIMERULE_H_


class KCDTimeRule: public FXFrame
{
	FXDECLARE(KCDTimeRule)

public:

  enum {
	ID_LAST = FXDialogBox::ID_LAST,
  };	

public:
	KCDTimeRule(FXComposite *p, 
		FXuint opts=FRAME_NORMAL, 
		FXint x=0, FXint y=0, FXint w=0, FXint h=0, 
		FXint pl=DEFAULT_PAD, FXint pr=DEFAULT_PAD, FXint pt=DEFAULT_PAD, FXint pb=DEFAULT_PAD);

	~KCDTimeRule() {}

	void Reset();
	
	void SetAudioTimeValue(FXint value);
	FXint GetAudioTimeValue();

	void SetDataTimeValue(FXint value);
	FXint GetDataTimeValue();

	long onPaint(FXObject* sender, FXSelector key, void* data);

private:
	KCDTimeRule() {}

private:
	FXint m_audioTime;
	FXint m_dataTime;
};

#endif

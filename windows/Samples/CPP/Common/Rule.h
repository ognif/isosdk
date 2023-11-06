#ifndef _KRULE_H_
#define _KRULE_H_


enum {
	CAPACITYRULE_CD		= 0x00080000,
	CAPACITYRULE_DVD	= 0x00100000
};

class KCDCapacityRule: public FXFrame
{
	FXDECLARE(KCDCapacityRule)

public:

  enum {
	ID_LAST = FXDialogBox::ID_LAST,
  };	

public:
	KCDCapacityRule(FXComposite *p, 
		FXuint opts=FRAME_NORMAL, 
		FXint x=0, FXint y=0, FXint w=0, FXint h=0, 
		FXint pl=DEFAULT_PAD, FXint pr=DEFAULT_PAD, FXint pt=DEFAULT_PAD, FXint pb=DEFAULT_PAD);

	~KCDCapacityRule();

	void SetSizeValue(FXlong size);
	FXlong GetSizeValue() const { return m_size*1024; }

	long onPaint(FXObject* sender, FXSelector key, void* data);

private:
	KCDCapacityRule();

private:
	FXint m_size;
};

#endif

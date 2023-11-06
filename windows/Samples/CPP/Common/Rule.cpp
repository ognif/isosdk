#include "stdafx.h"
#include "Rule.h"

FXDEFMAP(KCDCapacityRule) KCDCapacityRuleMap[] = {
	FXMAPFUNC(SEL_PAINT, 0, KCDCapacityRule::onPaint)
};

FXIMPLEMENT(KCDCapacityRule, FXFrame, KCDCapacityRuleMap, ARRAYNUMBER(KCDCapacityRuleMap))

KCDCapacityRule::KCDCapacityRule()
	: m_size(0)
{
}

KCDCapacityRule::KCDCapacityRule(FXComposite *p, 
		FXuint opts, 
		FXint x, FXint y, FXint w, FXint h, 
		FXint pl, FXint pr, FXint pt, FXint pb)
	: FXFrame(p, opts, x, y, w, h, pl, pr, pt, pb)	
	, m_size(0)
{	
}

KCDCapacityRule::~KCDCapacityRule()	
{
}

void KCDCapacityRule::SetSizeValue(FXlong size)
{
	m_size = (FXint)(size/1024);
	update();
}


long KCDCapacityRule::onPaint(FXObject* sender, FXSelector key, void* data)
{
	FXFrame::onPaint(sender, key, data);

	FXFont font(getApp(), "times", 8);
		font.create();

	FXint labelWidth = font.getTextWidth("5000MB");
	FXint capacity = CAPACITYRULE_DVD & this->options ? 4500*1024 : 700*1024; 
	FXint byteRange = capacity + capacity / 10;
	FXint width = getWidth();
	FXint bytesPerPixel = byteRange / (width + 1);
	FXint tickSpanInBytes = (bytesPerPixel * labelWidth * 2 / (50*1024)) * (50*1024) + (50*1024);
	FXint tickSpanInPx = tickSpanInBytes / (bytesPerPixel + 1);
	
	FXEvent *ev=(FXEvent*)data;
	FXDCWindow dc(this, ev);

	dc.setForeground(FXRGB(0,0,0));
	dc.setLineWidth(1);
	dc.setFont(&font);
	
	for (FXint x=0, bts = 0; x < width; x += tickSpanInPx, bts += tickSpanInBytes)
	{
		FXString strLabel;

		strLabel = FXString::value(bts/1024) + "MB";
		dc.drawLine(x,0,x,10);
		dc.drawText(x, 20, strLabel.text(), strLabel.length());
	}

	dc.setForeground(FXRGB(0,0,255));
	dc.setLineWidth(10);	
	dc.drawLine(0, 1, m_size / bytesPerPixel, 1);

	return 1;
}

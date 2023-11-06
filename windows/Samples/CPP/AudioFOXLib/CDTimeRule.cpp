#include "stdafx.h"
#include "CDTimeRule.h"

FXDEFMAP(KCDTimeRule) KCDTimeRuleMap[] = {
	FXMAPFUNC(SEL_PAINT, 0, KCDTimeRule::onPaint)
};

FXIMPLEMENT(KCDTimeRule, FXFrame, KCDTimeRuleMap, ARRAYNUMBER(KCDTimeRuleMap))

KCDTimeRule::KCDTimeRule(FXComposite *p, FXuint opts, FXint x, FXint y, FXint w, FXint h, FXint pl, FXint pr, FXint pt, FXint pb)
	: FXFrame(p, opts, x, y, w, h, pl, pr, pt, pb)	
	, m_audioTime(0)
	, m_dataTime(0)
{
}

void KCDTimeRule::SetAudioTimeValue(FXint value)
{
	m_audioTime = value;
	update();
}

void KCDTimeRule::SetDataTimeValue(FXint value)
{
	m_dataTime = value;
	update();
}

void KCDTimeRule::Reset()
{
	m_audioTime = 0;
	m_dataTime = 0;
	update();
}

FXint KCDTimeRule::GetAudioTimeValue()
{
	return m_audioTime;
}

FXint KCDTimeRule::GetDataTimeValue()
{
	return m_dataTime;
}

long KCDTimeRule::onPaint(FXObject* sender, FXSelector key, void* data)
{
	FXFrame::onPaint(sender, key, data);

	FXFont font(getApp(), "times", 8);
		font.create();

	FXint labelWidth = font.getTextWidth("100Min");
	FXint capacity = 80*60; // sec
	FXint timeRange = capacity + capacity / 10;
	FXint width = getWidth();
	FXint timePerPixel = timeRange / (width+1);
	FXint tickSpanInSec = (timePerPixel * labelWidth * 2 / (5*60)) * (5*60) + (5*60);
	FXint tickSpanInPx = tickSpanInSec / (timePerPixel + 1);

	//tickSpanInMin
	
	FXEvent *ev=(FXEvent*)data;
	FXDCWindow dc(this, ev);

	dc.setForeground(FXRGB(0,0,0));
	dc.setLineWidth(1);
	dc.setFont(&font);
	
	for (FXint x=0, sec = 0; x < width; x += tickSpanInPx, sec += tickSpanInSec)
	{
		FXString strLabel;

		strLabel = FXString::value(sec/60) + "Min";
		dc.drawLine(x,0,x,10);
		dc.drawText(x, 20, strLabel.text(), strLabel.length());
	}

	dc.setForeground(FXRGB(0,0,255));
	dc.setLineWidth(10);	
	dc.drawLine(0, 1, (m_dataTime + m_audioTime) / timePerPixel, 1);

	return 1;
}

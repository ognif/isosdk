// SizeRange.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "SizeRange.h"


// CSizeRange

IMPLEMENT_DYNAMIC(CSizeRange, CWnd)
CSizeRange::CSizeRange()
{
	m_CurrentPos = 0;
}

CSizeRange::~CSizeRange()
{
}


BEGIN_MESSAGE_MAP(CSizeRange, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CSizeRange-Meldungshandler
void CSizeRange::Attach(UINT control_id, CWnd *parent)
{
	m_Control = control_id;
	SubclassWindow(parent->GetDlgItem(control_id)->m_hWnd);
}

void CSizeRange::SetMaxRange(int max)
{
	m_MaxRange = max;
}

void CSizeRange::SetUnit(const char* strUnit)
{
	m_Unit = strUnit;
}

void CSizeRange::SetMarkTick(int tick)
{
	m_MarkTick = tick;
}

void CSizeRange::SetUnitTick(int tick) {
	m_UnitTick = tick;
}

void CSizeRange::AddLine(int pos, COLORREF color, bool bFullLine)
{
	LINE_DATA data;
	data.bFullLine = bFullLine;
	data.color = color;
	data.pos = pos;
	m_Lines.push_back(data);
}

void CSizeRange::RemoveAllLines() {
	m_Lines.clear();
}

void CSizeRange::SetValueColorChange(int pos, COLORREF coloref)
{
	COLOR_ZONE zone;
	zone.pos = pos;
	zone.color = coloref;
	m_ColorZones.push_back(zone);
}

void CSizeRange::ResetValueColorZones()
{
	m_ColorZones.clear();
}

void CSizeRange::SetValuePos(int pos) 
{
	m_CurrentPos = pos;
	//this->GetParent()->RedrawWindow();
}

int CSizeRange::GetValuePos()
{
	return m_CurrentPos;
}

void CSizeRange::DrawTicks(CDC *dc)
{
	int tickcount = m_MaxRange/m_MarkTick;
	double f = (double)m_DCx/(double)m_MaxRange;
	for(int i=0;i<tickcount;i++)
	{
		int curr_pos = (int)((i*m_MarkTick)*f);
		dc->MoveTo(curr_pos,0);
		dc->LineTo(curr_pos,int(m_DCy*0.2));
	}
}

void CSizeRange::DrawUnits(CDC *dc)
{	
	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));      
	lf.lfHeight = 15;                    
	_tcscpy(lf.lfFaceName, _T("Arial"));       
	font.CreateFontIndirect(&lf); 
	CObject *oldObject = dc->SelectObject(&font);

	dc->SetBkMode(TRANSPARENT);
	dc->SetTextAlign(TA_CENTER);
	int tickcount = m_MaxRange/m_UnitTick;
	double f = (double)m_DCx/(double)m_MaxRange;
	for(int i=0;i<tickcount+1;i++)
	{
		int curr_pos = (int)((i*m_UnitTick)*f);
		if(curr_pos<m_DCx*0.95)
		{
			dc->MoveTo(curr_pos,0);
			dc->LineTo(curr_pos,int(m_DCy*0.5));
			char text[125];
			sprintf(text,"%d%s",m_UnitTick*i,m_Unit);
			dc->TextOut(curr_pos,int(m_DCy*0.6),text);
		}
	}

	dc->SelectObject(&oldObject);
	font.DeleteObject();
}

void CSizeRange::DrawLines(CDC *dc)
{
	double f = (double)m_DCx/(double)m_MaxRange;
	int count = (int)m_Lines.size();
	for(int i=0;i<count;i++)
	{
		LINE_DATA data = m_Lines.at(i);
		CPen pen;
		if(data.bFullLine)
			pen.CreatePen(PS_SOLID, 2, data.color);
		else
			pen.CreatePen(PS_DOT, 2, data.color);
		CObject *old = dc->SelectObject(&pen);
		int curr_pos = (int)(data.pos*f);
		dc->MoveTo(curr_pos,0);
		dc->LineTo(curr_pos,m_DCy);
		dc->SelectObject(old);
		pen.DeleteObject();
	}
}

void CSizeRange::DrawValue(CDC *dc)
{
	int nbZones = (int)m_ColorZones.size();
	double f = (double)m_DCx/(double)m_MaxRange;

	int itmp;
	itmp = m_CurrentPos;
	if(m_CurrentPos > m_MaxRange)
		m_CurrentPos = m_MaxRange;

	for(int i=0;i<nbZones;i++)
	{
		COLOR_ZONE zone = m_ColorZones.at(i);
		if(m_CurrentPos>=zone.pos)
		{
			int theEnd = int(f*m_CurrentPos);
			dc->FillSolidRect(int(f*zone.pos+1), int(m_DCy*0.1+1), theEnd-int(f*zone.pos)+1, int(m_DCy*0.3)+1, RGB(50,50,50));
			dc->FillSolidRect(int(f*zone.pos), int(m_DCy*0.1), theEnd-int(f*zone.pos), int(m_DCy*0.3), zone.color);
		}
	}
	m_CurrentPos = itmp ;
}

void CSizeRange::DrawNew(CDC *dc){
	COLORREF m_BackColor(GetSysColor(COLOR_BTNFACE));
	
	CRect r;
	GetWindowRect(&r);
	ScreenToClient(r);
	dc->FillSolidRect(r,m_BackColor);
}

void CSizeRange::OnPaint()
{
	CPaintDC dc(this); // device context for painting
  
	//CDC *dc = GetDC();
	RECT r;
	GetWindowRect(&r);
	m_DCx = r.right - r.left;
	m_DCy = r.bottom - r.top;

	//Es müsste hier nun der Hintergrund neu gezeichnet werden.

	DrawNew(&dc);
	DrawTicks(&dc);
	DrawUnits(&dc);
	DrawLines(&dc);
	DrawValue(&dc);

	//CWnd::OnPaint(); //soll zum Zeichnen von Meldungen nicht aufgerufen werden.
}

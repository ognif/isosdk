#pragma once

#include <vector>


// CSizeRange
struct LINE_DATA 
{
	int pos;
	COLORREF color;
	bool bFullLine;
};

struct COLOR_ZONE
{
	int pos;
	COLORREF color;
};

class CSizeRange : public CWnd
{
	// setting vars
	int		m_MaxRange;
	int		m_MarkTick;
	int		m_UnitTick;
	UINT	m_Control;
	CString m_Unit;

	std::vector<LINE_DATA>	m_Lines;
	std::vector<COLOR_ZONE>	m_ColorZones;

	// Paint:
	   // Paint vars
	   int m_DCx;
	   int m_DCy;
	   // functions
	   void DrawTicks(CDC *dc);
	   void DrawUnits(CDC *dc);
	   void DrawLines(CDC *dc);
	   void DrawValue(CDC *dc);
	   void DrawNew(CDC *dc);

   int m_CurrentPos;

	DECLARE_DYNAMIC(CSizeRange)

public:
	CSizeRange();
	virtual ~CSizeRange();

	// settings
	void SetMaxRange(int max);
	void SetUnit(const char* strUnit);
	void SetMarkTick(int tick);
	void SetUnitTick(int tick);
	void AddLine(int pos,COLORREF color,bool bFullLine);
	void RemoveAllLines();

	void SetValueColorChange(int pos,COLORREF coloref);
	void ResetValueColorZones();

	void SetValuePos(int pos);
	int GetValuePos();

	void Attach(UINT control_id, CWnd *parent);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};



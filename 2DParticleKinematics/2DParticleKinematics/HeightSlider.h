#pragma once
#include "BasePanel.h"
class CHeightSlider :
	public CBasePanel
{
public:
	CHeightSlider();
	~CHeightSlider();
	void SetRange(int min, int max);
	void SetTicFreq(int freq) { m_nFreq = freq; }
	int GetPos() const { return m_nCurrentPos; }
	void SetPos(int pos);
	void SetToMin() { SetPos(m_nMin); }

private:
	COLORREF m_clrThumb;
	COLORREF m_clrThumbNA;
	COLORREF m_clrChannel;
	COLORREF m_clrTic;
	COLORREF m_clrTicNA;
	COLORREF m_clrBk;
	CRect m_rcChannel;
	CRect m_rcThumb;
	BOOL m_bIsActivated;
	CBrush* m_pBrushBk;
	CBrush* m_pBrushChannel;
	CBrush* m_pBrushThumb;
	HPEN m_hPenTic;
	HFONT m_hFontTic;
	CRect m_rcText;
	int m_nChannelLength;
	int m_nMin;
	int m_nMax;
	int m_nFreq;
	int m_nCurrentPos;
	BOOL m_bIsThumbSel;
	
public:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};


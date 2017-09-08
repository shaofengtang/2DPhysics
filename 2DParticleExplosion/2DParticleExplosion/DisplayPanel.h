#pragma once
#include "BasePanel.h"
#include "ParticleExplosion.h"

class CDisplayPanel :
	public CBasePanel
{
public:
	CDisplayPanel();
	~CDisplayPanel();

private:
	TParticleExplosion* m_particle;
	CBitmap* m_pPreBitmap;
	CBitmap* m_pMemBitmap;
	CDC* m_pMemDC;
	CBrush* m_pBkBrush;
	//HPEN m_hPrePen;
	//HBRUSH m_hPreBrush;

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg LRESULT OnFire(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnRefresh(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


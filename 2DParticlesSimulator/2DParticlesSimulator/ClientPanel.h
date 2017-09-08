#pragma once
#include "BasePanel.h"
#include "Particles.h"


class CClientPanel :
	public CBasePanel
{
public:
	CClientPanel();
	~CClientPanel();

private:
	CBitmap* m_pPreBitmap;
	CBitmap* m_pMemBitmap;
	CDC* m_pMemDC;
	HPEN m_hPenBk;
	HBRUSH m_hBrushBk;
	CParticles Units[_MAX_NUM_UNITS];
	CParticles Obstacles[_NUM_OBSTACLES];

public:
	void InitializeParticles();
	void DrawBkgnd();
	void DrawObstacles();
	bool CheckForCollisions(CParticles* p);

public:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


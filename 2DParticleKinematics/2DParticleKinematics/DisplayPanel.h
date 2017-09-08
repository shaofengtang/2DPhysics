#pragma once
#include "BasePanel.h"
class CDisplayPanel :
	public CBasePanel
{
public:
	CDisplayPanel();
	~CDisplayPanel();
	void Set2DPKV(double gravity, double alpha, double vm, double height) { m_2DPKV._2Dgravity = gravity; m_2DPKV._2Dalpha = alpha; m_2DPKV._2Dvm = vm; m_2DPKV._2Dheight = height; }
	void SetGunLen(int len) { m_nGunLength = len; }

private:
	struct _2DParticleKinematicV
	{
		double _2Dgravity;
		double _2Dalpha;
		double _2Dvm;
		double _2Dheight;
	} m_2DPKV;
	HPEN m_hPen;
	HPEN m_hPenTarget;
	HPEN m_hPenGun;
	HBRUSH m_hBrushGun;
	HBRUSH m_hBrushBk;
	CPoint m_ptCurrentPos;
	int m_nGunLength;
	CRect m_rcGun;
	CPoint m_ptGunEnd;
	CPoint m_ptTargetEnd;
	BOOL m_bIsFire;

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnGunChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnFire(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


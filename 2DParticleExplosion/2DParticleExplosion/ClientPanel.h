#pragma once
#include "BasePanel.h"
#include "ImageButton.h"
#include "EditControl.h"
#include "DisplayPanel.h"
#include "ParticleExplosion.h"

class CClientPanel :
	public CBasePanel
{
public:
	CClientPanel();
	~CClientPanel();

private:
	CImage m_imgClient;
	HPEN m_hPen;
	HFONT m_hFont;
	CImageButton m_btnClose;
	CImageButton m_btnFire;
	CImageButton m_btnRefresh;
	CEditControl m_editXPos;
	CEditControl m_editYPos;
	CEditControl m_editV0;
	CEditControl m_editGravity;
	CEditControl m_editDuration;
	CEditControl m_editAngle;
	CDisplayPanel m_displayPanel;
	MessagePacket* m_ppacket;

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnClickCloseBtn();
	afx_msg void OnClickRefreshBtn();
	afx_msg void OnClickFireBtn();
	afx_msg LRESULT OnRefresh(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnTabDown(WPARAM wParam, LPARAM lParam);
};


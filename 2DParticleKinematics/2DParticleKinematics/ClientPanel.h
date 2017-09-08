#pragma once
#include <atlimage.h>
#include "BasePanel.h"
#include "DisplayPanel.h"
#include "ImageButton.h"
#include "EditControl.h"
#include "HeightSlider.h"

class CClientPanel :
	public CBasePanel
{
public:
	CClientPanel();
	~CClientPanel();
	HWND GetDisplayWnd() const
	{
		if (m_displayPanel.m_hWnd)
		{
			return m_displayPanel.m_hWnd;
		}
		else return NULL;
	}

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClickCloseBtn();
	afx_msg void OnClickRefreshBtn();
	afx_msg void OnClickFireBtn();
	afx_msg LRESULT OnRefresh(WPARAM wParam, LPARAM lParam);

private:
	CImage m_imgClient;
	HPEN m_hPen;
	HFONT m_hFont;
	CImageButton m_btnFire;
	CImageButton m_btnRefresh;
	CImageButton m_btnClose;
	CEditControl m_editVm;
	CEditControl m_editG;
	CHeightSlider m_scHeight;
	CHeightSlider m_scAlpha;
	CDisplayPanel m_displayPanel;
};


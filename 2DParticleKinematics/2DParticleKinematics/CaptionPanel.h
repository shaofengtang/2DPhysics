#pragma once
#include <atlimage.h>
#include "BasePanel.h"
#include "ImageButton.h"

class CCaptionPanel :
	public CBasePanel
{
public:
	CCaptionPanel();
	~CCaptionPanel();
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClickMinBtn();
	afx_msg void OnClickClsBtn();

private:
	CImage m_imgCaption;
	CImageButton m_btnMin;
	CImageButton m_btnCls;
	HFONT m_hFont;
};


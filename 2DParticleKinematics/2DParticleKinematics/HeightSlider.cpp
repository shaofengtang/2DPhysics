#include "stdafx.h"
#include "HeightSlider.h"
#include "ClientPanel.h"


CHeightSlider::CHeightSlider()
{
	m_clrThumb = RGB(0, 130, 210);
	m_clrThumbNA = RGB(150, 150, 150);
	m_clrChannel = RGB(100, 100, 100);
	m_clrTic = RGB(255, 255, 255);
	m_clrTicNA = RGB(100, 100, 100);
	m_clrBk = RGB(45, 45, 45);
	m_rcChannel.SetRectEmpty();
	m_rcThumb.SetRectEmpty();
	m_bIsActivated = FALSE;
	m_pBrushBk = NULL;
	m_pBrushChannel = NULL;
	m_pBrushThumb = NULL;
	m_nMin = 0;
	m_nMax = 0;
	m_nFreq = 1;
	m_nCurrentPos = m_nMin;
	m_nChannelLength = 0;
	m_rcText.SetRectEmpty();
	m_bIsThumbSel = FALSE;
}


CHeightSlider::~CHeightSlider()
{
	if (m_pBrushBk) delete m_pBrushBk;
	if (m_pBrushChannel) delete m_pBrushChannel;
	if (m_pBrushThumb) delete m_pBrushThumb;
	DeleteObject(m_hFontTic);
	DeleteObject(m_hPenTic);
}
BEGIN_MESSAGE_MAP(CHeightSlider, CBasePanel)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()


int CHeightSlider::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBasePanel::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CRect rcClient;
	GetClientRect(rcClient);

	m_nChannelLength = rcClient.Height() - 50;

	m_rcChannel.top = rcClient.top + 2;
	m_rcChannel.bottom = m_rcChannel.top + m_nChannelLength;
	m_rcChannel.left = rcClient.Width() / 2 - 2;
	m_rcChannel.right = rcClient.Width() / 2 + 2;

	m_rcThumb.bottom = m_rcChannel.bottom + 2;
	m_rcThumb.top = m_rcChannel.bottom - 2;
	m_rcThumb.left = rcClient.Width() / 2 - 7;
	m_rcThumb.right = rcClient.Width() / 2 + 7;

	m_hFontTic = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, _T("微软雅黑"));
	m_hPenTic = CreatePen(PS_SOLID, 1, m_clrTicNA);

	m_rcText = rcClient;
	m_rcText.top = rcClient.bottom - 30;

	return 0;
}


void CHeightSlider::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CBasePanel::OnPaint()
	
	CRect rcClient;
	GetClientRect(rcClient);

	/*CDC dcMem;
	CBitmap bmp;
	dcMem.CreateCompatibleDC(&dc);
	bmp.CreateCompatibleBitmap(&dcMem, rcClient.Width(), rcClient.Height());
	dcMem.SelectObject(&bmp);*/

	if (m_pBrushBk) delete m_pBrushBk;
	m_pBrushBk = new CBrush(m_clrBk);
	dc.FillRect(rcClient, m_pBrushBk);

	if (m_pBrushChannel) delete m_pBrushChannel;
	m_pBrushChannel = new CBrush(m_clrChannel);
	if (!m_bIsActivated)
	{
		if (m_pBrushThumb) delete m_pBrushThumb;
		m_pBrushThumb = new CBrush(m_clrThumbNA);

		DeleteObject(m_hPenTic);
		m_hPenTic = CreatePen(PS_SOLID, 1, m_clrTicNA);

		dc.SetTextColor(m_clrTicNA);
	}
	else
	{
		if (m_pBrushThumb) delete m_pBrushThumb;
		m_pBrushThumb = new CBrush(m_clrThumb);

		DeleteObject(m_hPenTic);
		m_hPenTic = CreatePen(PS_SOLID, 1, m_clrTic);

		dc.SetTextColor(m_clrTic);
	}

	dc.FillRect(m_rcChannel, m_pBrushChannel);
	dc.FillRect(m_rcThumb, m_pBrushThumb);

	HPEN hPrePen = (HPEN)dc.SelectObject(m_hPenTic);
	double increment = (double)m_rcChannel.Height() / (double)m_nFreq;
	for (int i = 0; i <= m_nFreq; i++)
	{
		dc.MoveTo(m_rcThumb.left - 7, m_rcChannel.bottom - i * increment);
		if (i == 0 || i == m_nFreq)
		{
			dc.LineTo(m_rcThumb.left - 7 - 10, m_rcChannel.bottom - i * increment);
		}
		else
		{
			dc.LineTo(m_rcThumb.left - 7 - 5, m_rcChannel.bottom - i * increment);
		}
		dc.MoveTo(m_rcThumb.right + 7, m_rcChannel.bottom - i * increment);
		if (i == 0 || i == m_nFreq)
		{
			dc.LineTo(m_rcThumb.right + 7 + 10, m_rcChannel.bottom - i * increment);
		}
		else
		{
			dc.LineTo(m_rcThumb.right + 7 + 5, m_rcChannel.bottom - i * increment);
		}
	}
	dc.SelectObject(hPrePen);

	HFONT hPreFont = (HFONT)dc.SelectObject(m_hFontTic);
	int nBkMode = dc.SetBkMode(TRANSPARENT);
	CString strText;
	strText.Format(_T("%d"), m_nCurrentPos);
	dc.DrawText(strText, m_rcText, DT_CENTER | DT_VCENTER);
	dc.SetBkMode(nBkMode);
	dc.SelectObject(hPreFont);

	/*dc.BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &dcMem, 0, 0, SRCCOPY);
	dcMem.DeleteDC();
	bmp.DeleteObject();*/
}

void CHeightSlider::SetRange(int min, int max)
{
	if (min <= max)
	{
		m_nMin = min;
		m_nMax = max;
	}
	else
	{
		m_nMax = min;
		m_nMin = max;
	}
}

void CHeightSlider::SetPos(int pos)
{
	if (pos < m_nMin)
	{
		m_nCurrentPos = m_nMin;
	}
	else if (pos > m_nMax)
	{
		m_nCurrentPos = m_nMax;
	}
	else
	{
		m_nCurrentPos = pos;
	}

	CRect rc = m_rcThumb;

	double proportion = (double)(m_nCurrentPos - m_nMin) / (double)(m_nMax - m_nMin);
	int nCenterOfThumb = proportion * m_rcChannel.Height();
	m_rcThumb.top = m_rcChannel.bottom - nCenterOfThumb - 2;
	m_rcThumb.bottom = m_rcChannel.bottom - nCenterOfThumb + 2;

	rc.top = (rc.top < m_rcThumb.top) ? rc.top : m_rcThumb.top;
	rc.bottom = (rc.bottom > m_rcThumb.bottom) ? rc.bottom : m_rcThumb.bottom;
	InvalidateRect(rc);
	InvalidateRect(m_rcText);

	CClientPanel* pWnd = (CClientPanel*)GetParent();
	if (pWnd)
	{
		
		::SendMessage(pWnd->GetDisplayWnd(), WM_GUNCHANGE, this->GetDlgCtrlID(), MAKELPARAM(m_nCurrentPos, m_nMax - m_nMin));
	}
	
	// Invalidate();
}

void CHeightSlider::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetFocus();
	if (m_rcThumb.PtInRect(point))
	{
		m_bIsThumbSel = TRUE;
	}
	else if (m_rcChannel.PtInRect(point))
	{
		int pos = m_nMin + (double)(m_rcChannel.bottom - point.y) / (double)m_rcChannel.Height() * (m_nMax - m_nMin);
		SetPos(pos);
	}

	CBasePanel::OnLButtonDown(nFlags, point);
}


void CHeightSlider::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nFlags == MK_LBUTTON && m_bIsThumbSel)
	{
		int pos = m_nMin + (double)(m_rcChannel.bottom - point.y) / (double)m_rcChannel.Height() * (m_nMax - m_nMin);
		SetPos(pos);
	}
	CBasePanel::OnMouseMove(nFlags, point);
}


BOOL CHeightSlider::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	// return CBasePanel::OnEraseBkgnd(pDC);
	return 1;
}


void CHeightSlider::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bIsThumbSel) m_bIsThumbSel = FALSE;
	CBasePanel::OnLButtonUp(nFlags, point);
}


void CHeightSlider::OnSetFocus(CWnd* pOldWnd)
{
	CBasePanel::OnSetFocus(pOldWnd);

	// TODO: 在此处添加消息处理程序代码
	m_bIsActivated = TRUE;
	Invalidate();
}


void CHeightSlider::OnKillFocus(CWnd* pNewWnd)
{
	CBasePanel::OnKillFocus(pNewWnd);

	// TODO: 在此处添加消息处理程序代码
	m_bIsActivated = FALSE;
	Invalidate();
}

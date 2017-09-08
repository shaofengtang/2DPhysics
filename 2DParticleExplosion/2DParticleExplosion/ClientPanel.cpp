#include "stdafx.h"
#include "ClientPanel.h"
#include "Resource.h"
#include "MainFrame.h"


CClientPanel::CClientPanel()
{
	m_btnClose.m_hWnd = NULL;
	m_btnFire.m_hWnd = NULL;
	m_btnRefresh.m_hWnd = NULL;
	m_editXPos.m_hWnd = NULL;
	m_editYPos,m_hWnd = NULL;
	m_editV0.m_hWnd = NULL;
	m_editGravity.m_hWnd = NULL;
	m_editDuration.m_hWnd = NULL;
	m_editAngle.m_hWnd = NULL;
	m_displayPanel.m_hWnd = NULL;
	m_ppacket = NULL;
}


CClientPanel::~CClientPanel()
{
	DeleteObject(m_hPen);
	DeleteObject(m_hFont);
	if (m_ppacket) delete m_ppacket;
}
BEGIN_MESSAGE_MAP(CClientPanel, CBasePanel)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CLOSEBTN, OnClickCloseBtn)
	ON_BN_CLICKED(IDC_REFRESHBTN, OnClickRefreshBtn)
	ON_BN_CLICKED(IDC_FIREBTN, OnClickFireBtn)
	ON_MESSAGE(WM_REFRESH, OnRefresh)
	ON_MESSAGE(WM_TABDOWN, OnTabDown)
END_MESSAGE_MAP()


int CClientPanel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBasePanel::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	if (m_imgClient.IsNull())
	{
		m_imgClient.LoadFromResource(AfxGetInstanceHandle(), IDB_DARKGRAY);
	}

	if (m_displayPanel.m_hWnd == NULL)
	{
		m_displayPanel.Create(_T("DisplayPanel"), WS_CHILD | WS_VISIBLE, CRect(200, 10, lpCreateStruct->cx - 10, lpCreateStruct->cy - 10), this, 10001);
	}

	if (m_btnFire.m_hWnd == NULL)
	{
		m_btnFire.Create(_T("FireButton"), WS_CHILD | WS_VISIBLE, CRect(50, 455, 150, 485), this, IDC_FIREBTN);
		m_btnFire.SetImage(IDB_FIREBTN);
	}

	if (m_btnRefresh.m_hWnd == NULL)
	{
		m_btnRefresh.Create(_T("RefreshButton"), WS_CHILD | WS_VISIBLE, CRect(50, 522, 150, 552), this, IDC_REFRESHBTN);
		m_btnRefresh.SetImage(IDB_REFRESHBTN);
	}

	if (m_btnClose.m_hWnd == NULL)
	{
		m_btnClose.Create(_T("CloseButton"), WS_CHILD | WS_VISIBLE, CRect(50, 590, 150, 620), this, IDC_CLOSEBTN);
		m_btnClose.SetImage(IDB_CLOSEBTN);
	}

	if (m_editXPos.m_hWnd == NULL)
	{
		m_editXPos.Create(WS_CHILD | WS_VISIBLE | ES_LEFT, CRect(80, 35, 170, 65), this, IDC_XPOSEDIT);
		m_editXPos.SetMargins(5, 0);
	}

	if (m_editYPos.m_hWnd == NULL)
	{
		m_editYPos.Create(WS_CHILD | WS_VISIBLE | ES_LEFT, CRect(80, 95, 170, 125), this, IDC_YPOSEDIT);
		m_editYPos.SetMargins(5, 0);
	}

	if (m_editV0.m_hWnd == NULL)
	{
		m_editV0.Create(WS_CHILD | WS_VISIBLE | ES_LEFT, CRect(80, 155, 170, 185), this, IDC_V0EDIT);
		m_editV0.SetMargins(5, 0);
	}

	if (m_editDuration.m_hWnd == NULL)
	{
		m_editDuration.Create(WS_CHILD | WS_VISIBLE | ES_LEFT, CRect(80, 215, 170, 245), this, IDC_DURATIONEDIT);
		m_editDuration.SetMargins(5, 0);
	}

	if (m_editGravity.m_hWnd == NULL)
	{
		m_editGravity.Create(WS_CHILD | WS_VISIBLE | ES_LEFT, CRect(80, 275, 170, 305), this, IDC_GRAVITYEDIT);
		m_editGravity.SetMargins(5, 0);
	}

	if (m_editAngle.m_hWnd == NULL)
	{
		m_editAngle.Create(WS_CHILD | WS_VISIBLE | ES_LEFT, CRect(80, 335, 170, 365), this, IDC_ANGLEEDIT);
		m_editAngle.SetMargins(5, 0);
	}

	m_hPen = CreatePen(PS_SOLID, 1, RGB(100, 100, 100));
	m_hFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, _T("微软雅黑"));

	m_editXPos.SetFocus();

	return 0;
}


void CClientPanel::OnSize(UINT nType, int cx, int cy)
{
	CBasePanel::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rcClient;
	GetClientRect(rcClient);

	if (m_displayPanel.m_hWnd)
	{
		CRect rcDisplay = rcClient;
		rcDisplay.left = 200;
		rcDisplay.right -= 10;
		rcDisplay.top = 10;
		rcDisplay.bottom -= 10;
		m_displayPanel.MoveWindow(rcDisplay);
	}
}


void CClientPanel::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CBasePanel::OnPaint()

	CRect rcClient;
	GetClientRect(rcClient);
	if (!m_imgClient.IsNull())
	{
		m_imgClient.Draw(dc.m_hDC, rcClient);
	}

	HPEN hPrePen = (HPEN)dc.SelectObject(m_hPen);
	dc.MoveTo(10, 10);
	dc.LineTo(190, 10);
	dc.LineTo(190, 410);
	dc.LineTo(10, 410);
	dc.LineTo(10, 10);

	dc.MoveTo(10, 420);
	dc.LineTo(190, 420);
	dc.LineTo(190, rcClient.bottom - 10);
	dc.LineTo(10, rcClient.bottom - 10);
	dc.LineTo(10, 420);

	HFONT hPreFont = (HFONT)dc.SelectObject(m_hFont);
	int nPreBkMode = dc.SetBkMode(TRANSPARENT);
	COLORREF cPreColor = dc.SetTextColor(RGB(255, 255, 255));
	dc.DrawText(_T("X Pos"), CRect(10, 40, 70, 60), DT_VCENTER | DT_RIGHT | DT_SINGLELINE);
	dc.DrawText(_T("Y Pos"), CRect(10, 100, 70, 120), DT_VCENTER | DT_RIGHT | DT_SINGLELINE);
	dc.DrawText(_T("V0"), CRect(10, 160, 70, 180), DT_VCENTER | DT_RIGHT | DT_SINGLELINE);
	dc.DrawText(_T("Duration"), CRect(10, 220, 70, 240), DT_VCENTER | DT_RIGHT | DT_SINGLELINE);
	dc.DrawText(_T("Gravity"), CRect(10, 280, 70, 300), DT_VCENTER | DT_RIGHT | DT_SINGLELINE);
	dc.DrawText(_T("Angle"), CRect(10, 340, 70, 360), DT_VCENTER | DT_RIGHT | DT_SINGLELINE);

	dc.SelectObject(hPreFont);
	dc.SetBkMode(nPreBkMode);
	dc.SetTextColor(cPreColor);
	dc.SelectObject(hPrePen);
}

void CClientPanel::OnClickCloseBtn()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if (pMainFrame)
	{
		pMainFrame->SendMessage(WM_SYSCOMMAND, SC_CLOSE, 0);
	}
}

void CClientPanel::OnClickRefreshBtn()
{
	::SendMessage(this->m_hWnd, WM_REFRESH, 0, 0);
	m_displayPanel.SendMessage(WM_REFRESH, 0, 0);
}

LRESULT CClientPanel::OnRefresh(WPARAM wParam, LPARAM lParam)
{
	
	::SetDlgItemText(this->m_hWnd, IDC_XPOSEDIT, _T(""));
	::SetDlgItemText(this->m_hWnd, IDC_YPOSEDIT, _T(""));
	::SetDlgItemText(this->m_hWnd, IDC_V0EDIT, _T(""));
	::SetDlgItemText(this->m_hWnd, IDC_DURATIONEDIT, _T(""));
	::SetDlgItemText(this->m_hWnd, IDC_GRAVITYEDIT, _T(""));
	::SetDlgItemText(this->m_hWnd, IDC_ANGLEEDIT, _T(""));

	if (m_ppacket) delete m_ppacket;
	
	return TRUE;
}

void CClientPanel::OnClickFireBtn()
{
	CString strX, strY, strG, strD, strA, strV;

	GetDlgItem(IDC_XPOSEDIT)->GetWindowText(strX);
	if (strX.IsEmpty())
	{
		MessageBox(_T("The X Pos is empty."));
		return;
	}

	GetDlgItem(IDC_YPOSEDIT)->GetWindowText(strY);
	if (strY.IsEmpty())
	{
		MessageBox(_T("The Y Pos is empty."));
		return;
	}

	GetDlgItem(IDC_V0EDIT)->GetWindowText(strV);
	if (strV.IsEmpty())
	{
		MessageBox(_T("The V0 is empty."));
		return;
	}

	GetDlgItem(IDC_GRAVITYEDIT)->GetWindowText(strG);
	if (strG.IsEmpty())
	{
		MessageBox(_T("The Gravity is empty."));
		return;
	}

	GetDlgItem(IDC_DURATIONEDIT)->GetWindowText(strD);
	if (strD.IsEmpty())
	{
		MessageBox(_T("The Duration is empty."));
		return;
	}

	GetDlgItem(IDC_ANGLEEDIT)->GetWindowText(strA);
	if (strA.IsEmpty())
	{
		MessageBox(_T("The Angle is empty."));
		return;
	}

	float fx = _ttof(strX);
	float fy = _ttof(strY);
	float fg = _ttof(strG);
	float fd = _ttof(strD);
	float fa = _ttof(strA);
	float fv = _ttof(strV);

	if (m_ppacket) delete m_ppacket;
	m_ppacket = new _Packet(fx, fy, fv, fg, fa, fd);

	::SendMessage(m_displayPanel.m_hWnd, WM_FIRE, 0, (LPARAM)m_ppacket);
}

LRESULT CClientPanel::OnTabDown(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case IDC_XPOSEDIT:
		m_editYPos.SetFocus();
		break;

	case IDC_YPOSEDIT:
		m_editV0.SetFocus();
		break;

	case IDC_V0EDIT:
		m_editDuration.SetFocus();
		break;

	case IDC_DURATIONEDIT:
		m_editGravity.SetFocus();
		break;

	case IDC_GRAVITYEDIT:
		m_editAngle.SetFocus();
		break;

	case IDC_ANGLEEDIT:
		m_editXPos.SetFocus();
		break;

	default:
		break;
	}

	return TRUE;
}

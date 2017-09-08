#include "stdafx.h"
#include "ClientPanel.h"
#include "resource.h"
#include "MainFrame.h"
#include "Utility.h"


CClientPanel::CClientPanel()
{
	m_displayPanel.m_hWnd = NULL;
	m_hPen = CreatePen(PS_SOLID, 1, RGB(100, 100, 100));
	m_hFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, _T("微软雅黑"));
	m_btnFire.m_hWnd = NULL;
	m_btnRefresh.m_hWnd = NULL;
	m_btnClose.m_hWnd = NULL;
	m_editVm.m_hWnd = NULL;
	m_editG.m_hWnd = NULL;
	m_scHeight.m_hWnd = NULL;
	m_scAlpha.m_hWnd = NULL;
}


CClientPanel::~CClientPanel()
{
	DeleteObject(m_hPen);
	DeleteObject(m_hFont);
}
BEGIN_MESSAGE_MAP(CClientPanel, CBasePanel)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_CLOSEBTN, OnClickCloseBtn)
	ON_BN_CLICKED(IDC_REFRESHBTN, OnClickRefreshBtn)
	ON_BN_CLICKED(IDC_FIREBTN, OnClickFireBtn)
	ON_MESSAGE(WM_REFRESH, OnRefresh)
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

	if (m_editVm.m_hWnd == NULL)
	{
		m_editVm.Create(WS_CHILD | WS_VISIBLE | ES_LEFT, CRect(60, 315, 170, 345), this, IDC_VMEDIT);
		m_editVm.SetMargins(5, 0);
	}

	if (m_editG.m_hWnd == NULL)
	{
		m_editG.Create(WS_CHILD | WS_VISIBLE | ES_LEFT, CRect(60, 365, 170, 395), this, IDC_GEDIT);
		m_editG.SetMargins(5, 0);
	}

	if (m_scHeight.m_hWnd == NULL)
	{
		m_scHeight.Create(_T("HeightSliderControl"), WS_CHILD | WS_VISIBLE, CRect(15, 40, 90, 285), this, IDC_HEIGHTSC);
		m_scHeight.SetRange(0, 100);
		m_scHeight.SetTicFreq(10);
		m_scHeight.SetPos(50);
	}

	if (m_scAlpha.m_hWnd == NULL)
	{
		m_scAlpha.Create(_T("AlphaSliderControl"), WS_CHILD | WS_VISIBLE, CRect(110, 40, 185, 285), this, IDC_ALPHASC);
		m_scAlpha.SetRange(0, 180);
		m_scAlpha.SetTicFreq(18);
		m_scAlpha.SetPos(90);
	}
	
	return 0;
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

	// framework
	HPEN hPrePen = (HPEN)dc.SelectObject(m_hPen);
	dc.MoveTo(10, 10);
	dc.LineTo(95, 10);
	dc.LineTo(95, 290);
	dc.LineTo(10, 290);
	dc.LineTo(10, 10);

	dc.MoveTo(105, 10);
	dc.LineTo(190, 10);
	dc.LineTo(190, 290);
	dc.LineTo(105, 290);
	dc.LineTo(105, 10);

	dc.MoveTo(10, 300);
	dc.LineTo(190, 300);
	dc.LineTo(190, 410);
	dc.LineTo(10, 410);
	dc.LineTo(10, 300);

	dc.MoveTo(10, 420);
	dc.LineTo(190, 420);
	dc.LineTo(190, rcClient.bottom - 10);
	dc.LineTo(10, rcClient.bottom - 10);
	dc.LineTo(10, 420);

	HFONT hPreFont = (HFONT)dc.SelectObject(m_hFont);
	int nPreBkMode = dc.SetBkMode(TRANSPARENT);
	COLORREF cPreColor = dc.SetTextColor(RGB(255, 255, 255));
	dc.DrawText(_T("Height"), CRect(10, 15, 95, 35), DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS);
	dc.DrawText(_T("Alpha"), CRect(105, 15, 190, 35), DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS);
	dc.DrawText(_T("Vm"), CRect(10, 320, 50, 340), DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS);
	dc.DrawText(_T("g"), CRect(10, 370, 50, 390), DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS);

	dc.SelectObject(hPreFont);
	dc.SetBkMode(nPreBkMode);
	dc.SetTextColor(cPreColor);
	dc.SelectObject(hPrePen);
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

	if (m_scHeight.m_hWnd)
	{
		m_scHeight.MoveWindow(CRect(15, 40, 90, 285));
	}

	if (m_scAlpha.m_hWnd)
	{
		m_scAlpha.MoveWindow(CRect(110, 40, 185, 285));
	}
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
}

LRESULT CClientPanel::OnRefresh(WPARAM wParam, LPARAM lParam)
{
	m_scHeight.SetPos(50);
	m_scAlpha.SetPos(90);
	::SetDlgItemText(this->m_hWnd, IDC_VMEDIT, _T(""));
	::SetDlgItemText(this->m_hWnd, IDC_GEDIT, _T(""));

	return TRUE;
}

void CClientPanel::OnClickFireBtn()
{
	CString strVm, strG;
	GetDlgItem(IDC_VMEDIT)->GetWindowText(strVm);
	GetDlgItem(IDC_GEDIT)->GetWindowText(strG);
	g_Vm = _ttof(strVm);
	g_G = _ttof(strG);
	::SendMessage(m_displayPanel.m_hWnd, WM_FIRE, 0, 0);
}
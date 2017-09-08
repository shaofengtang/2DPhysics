#include "stdafx.h"
#include "DisplayPanel.h"
#include "Utility.h"

const double PI = 3.1415;

CDisplayPanel::CDisplayPanel()
{
	m_rcGun.SetRectEmpty();
	m_bIsFire = FALSE;
}


CDisplayPanel::~CDisplayPanel()
{
	DeleteObject(m_hPen);
	DeleteObject(m_hPenGun);
	DeleteObject(m_hPenTarget);
	DeleteObject(m_hBrushGun);
	DeleteObject(m_hBrushBk);
}
BEGIN_MESSAGE_MAP(CDisplayPanel, CBasePanel)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_MESSAGE(WM_GUNCHANGE, OnGunChanged)
	ON_MESSAGE(WM_FIRE, OnFire)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


void CDisplayPanel::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CBasePanel::OnPaint()

	CRect rcClient;
	GetClientRect(rcClient);

	CDC dcMem;
	CBitmap bmp;
	dcMem.CreateCompatibleDC(&dc);
	bmp.CreateCompatibleBitmap(&dcMem, rcClient.Width(), rcClient.Height());
	dcMem.SelectObject(&bmp);

	HBRUSH hPreBrush = (HBRUSH)dcMem.SelectObject(m_hBrushBk);
	dcMem.Rectangle(rcClient);

	HPEN hPrePen = (HPEN)dcMem.SelectObject(m_hPenGun);
	dcMem.SelectObject(m_hBrushGun);
	dcMem.Ellipse(m_rcGun);
	dcMem.MoveTo(0, (m_rcGun.top + m_rcGun.bottom) / 2);
	dcMem.LineTo(m_ptGunEnd);

	dcMem.SelectObject(m_hPenTarget);
	dcMem.LineTo(m_ptTargetEnd);

	dcMem.SelectObject(hPrePen);
	dcMem.SelectObject(hPreBrush);

	if (m_bIsFire)
	{
		dcMem.SelectObject(m_hPen);
		int t = 1.0;
		while (m_ptCurrentPos.x <= rcClient.right && m_ptCurrentPos.y <= rcClient.bottom)
		{
			dcMem.MoveTo(m_ptCurrentPos);
			m_ptCurrentPos.x = m_ptGunEnd.x + m_2DPKV._2Dvm * sin(m_2DPKV._2Dalpha * PI / 180.0) * t;
			m_ptCurrentPos.y = m_ptGunEnd.y + m_2DPKV._2Dvm * cos(m_2DPKV._2Dalpha * PI / 180.0) * t + 0.5 * m_2DPKV._2Dgravity * t * t;
			dcMem.LineTo(m_ptCurrentPos);
			t = t + 1.0;
		}
		m_ptCurrentPos = m_ptGunEnd;
	}

	dc.BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &dcMem, 0, 0, SRCCOPY);
	dcMem.DeleteDC();
	bmp.DeleteObject();
}


int CDisplayPanel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBasePanel::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CRect rcClient;
	GetClientRect(rcClient);

	Set2DPKV(0.0, 90.0, 0.0, rcClient.Height() / 2);
	m_nGunLength = 20;
	m_ptGunEnd.x = 20;
	m_ptGunEnd.y = rcClient.Height() / 2;
	m_ptTargetEnd.x = rcClient.right;
	m_ptTargetEnd.y = rcClient.Height() / 2;
	m_rcGun.top = rcClient.Height() / 2 - 10;
	m_rcGun.bottom = rcClient.Height() / 2 + 10;
	m_rcGun.left = -10;
	m_rcGun.right = 10;
	m_ptCurrentPos = m_ptGunEnd;

	m_hPenGun = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	m_hBrushGun = CreateSolidBrush(RGB(0, 0, 0));
	
	m_hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_hPenTarget = CreatePen(PS_DASH, 1, RGB(70, 70, 70));

	m_hBrushBk = CreateSolidBrush(RGB(255, 255, 255));

	return 0;
}

LRESULT CDisplayPanel::OnGunChanged(WPARAM wParam, LPARAM lParam)
{
	CString str;
	double proportion;
	CRect rcClient;
	GetClientRect(rcClient);
	CRect rcPreGun = m_rcGun;
	int move;

	m_bIsFire = FALSE;

	switch (wParam)
	{
	case IDC_HEIGHTSC:
		proportion = (double)LOWORD(lParam) / (double)HIWORD(lParam);
		m_rcGun.top = rcClient.Height() * (1 - proportion) - 10;
		m_rcGun.bottom = rcClient.Height() * (1 - proportion) + 10;
		m_2DPKV._2Dheight = rcClient.Height() - (m_rcGun.top + m_rcGun.bottom) / 2;
		move = m_rcGun.top - rcPreGun.top;
		m_ptGunEnd.y += move;
		if (m_2DPKV._2Dalpha == 0.0)
		{
			m_ptTargetEnd.x = 0;
			m_ptTargetEnd.y = rcClient.bottom;
		}
		else if (m_2DPKV._2Dalpha == 180.0)
		{
			m_ptTargetEnd.x = 0;
			m_ptTargetEnd.y = 0;
		}
		else
		{
			m_ptTargetEnd.x = rcClient.right;
			m_ptTargetEnd.y = (m_rcGun.top + m_rcGun.bottom) / 2 + rcClient.Width() / tan(m_2DPKV._2Dalpha * PI / 180.0);
		}
		break;

	case IDC_ALPHASC:
		m_2DPKV._2Dalpha = (double)LOWORD(lParam);
		m_ptGunEnd.x = m_nGunLength * sin(m_2DPKV._2Dalpha * PI / 180);
		m_ptGunEnd.y = (m_rcGun.top + m_rcGun.bottom) / 2 + m_nGunLength * cos(m_2DPKV._2Dalpha * PI / 180);
		if (m_2DPKV._2Dalpha == 0.0)
		{
			m_ptTargetEnd.x = 0;
			m_ptTargetEnd.y = rcClient.bottom;
		}
		else if (m_2DPKV._2Dalpha == 180.0)
		{
			m_ptTargetEnd.x = 0;
			m_ptTargetEnd.y = 0;
		}
		else
		{
			m_ptTargetEnd.x = rcClient.right;
			m_ptTargetEnd.y = (m_rcGun.top + m_rcGun.bottom) / 2 + rcClient.Width() / tan(m_2DPKV._2Dalpha * PI / 180);
		}
		break;

	default:
		break;
	}

	m_ptCurrentPos = m_ptGunEnd;
	Invalidate();

	return TRUE;
}

BOOL CDisplayPanel::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	// return CBasePanel::OnEraseBkgnd(pDC);
	return 1;
}

LRESULT CDisplayPanel::OnFire(WPARAM wParam, LPARAM lParam)
{
	CString str1, str2, str3, str4, strout;
	//str1.Format(_T("%f"), g_Vm);
	//str2.Format(_T("%f"), g_G);
	//CString strout = _T("Vm: ") + str1 + _T(" G: ") + str2;
	//MessageBox(strout);
	m_2DPKV._2Dgravity = g_G;
	m_2DPKV._2Dvm = g_Vm;
	m_bIsFire = TRUE;
	/*str1.Format(_T("%f"), m_2DPKV._2Dvm);
	str2.Format(_T("%f"), m_2DPKV._2Dgravity);
	str3.Format(_T("%f"), m_2DPKV._2Dheight);
	str4.Format(_T("%f"), m_2DPKV._2Dalpha);
	strout = _T("Vm: ") + str1 + _T("G: ") + str2 + _T("Height: ") + str3 + _T("Alpha: ") + str4;
	MessageBox(strout);*/
	Invalidate();
	return TRUE;
}
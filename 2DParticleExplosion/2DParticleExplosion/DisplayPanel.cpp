#include "stdafx.h"
#include "DisplayPanel.h"

CDisplayPanel::CDisplayPanel()
{
	m_particle = NULL;
	m_pPreBitmap = NULL;
	m_pMemBitmap = NULL;
	m_pMemDC = NULL;
	m_pBkBrush = NULL;
}


CDisplayPanel::~CDisplayPanel()
{
	if (m_particle) delete m_particle;
	delete m_pMemDC;
	delete m_pMemBitmap;
	delete m_pBkBrush;
	//DeleteObject(m_hPrePen);
	//DeleteObject(m_hPreBrush);
}
BEGIN_MESSAGE_MAP(CDisplayPanel, CBasePanel)
	ON_WM_PAINT()
	ON_MESSAGE(WM_FIRE, OnFire)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_MESSAGE(WM_REFRESH, OnRefresh)
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


void CDisplayPanel::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CBasePanel::OnPaint()
	CRect rcClient;
	GetClientRect(rcClient);

	/*CDC dcMem;
	CBitmap bmp;
	dcMem.CreateCompatibleDC(&dc);
	bmp.CreateCompatibleBitmap(&dc, rcClient.Width(), rcClient.Height());
	dcMem.SelectObject(&bmp);*/

	//m_pMemDC->SelectObject(m_hPrePen);
	//m_pMemDC->SelectObject(m_hPreBrush);
	//m_pMemDC->Rectangle(rcClient);
	m_pMemDC->FillRect(rcClient, m_pBkBrush);
	if (m_particle && m_particle->m_active)
	{
		for (int i = 0; i < MAXPARTICLES; i++)
		{
			COLORREF clr = RGB(m_particle->m_explosion[i].r, m_particle->m_explosion[i].g, m_particle->m_explosion[i].b);
			HPEN hPen = CreatePen(PS_SOLID, 1, clr);
			HBRUSH hBrush = CreateSolidBrush(clr);
			CRect rc;
			rc.left = m_particle->m_x + m_particle->m_explosion[i].x - 2;
			rc.right = m_particle->m_x + m_particle->m_explosion[i].x + 2;
			rc.top = m_particle->m_y + m_particle->m_explosion[i].y - 2;
			rc.bottom = m_particle->m_y + m_particle->m_explosion[i].y + 2;
			m_pMemDC->SelectObject(hPen);
			m_pMemDC->SelectObject(hBrush);
			m_pMemDC->Ellipse(rc);
			DeleteObject(hPen);
			DeleteObject(hBrush);
			//dcMem.SetPixel(m_particle->m_x + m_particle->m_explosion[i].x, m_particle->m_y + m_particle->m_explosion[i].y, RGB(255, 0, 0));
		}
	}
	else if (m_particle && !m_particle->m_active)
	{
		KillTimer(1);
	}

	dc.BitBlt(0, 0, rcClient.Width(), rcClient.Height(), m_pMemDC, 0, 0, SRCCOPY);

	//dcMem.DeleteDC();
	//bmp.DeleteObject();
}

LRESULT CDisplayPanel::OnFire(WPARAM wParam, LPARAM lParam)
{
	//CString strX, strY, strA, strD, strG, strV;
	MessagePacket* tmp = (MessagePacket*)lParam;
	if (m_particle)
	{
		KillTimer(1);
		delete m_particle;
	}
	m_particle = new TParticleExplosion();
	m_particle->CreateParticleExplosion(tmp->m_x, tmp->m_y, tmp->m_v, tmp->m_d, tmp->m_g, tmp->m_a);
	SetTimer(1, 50, NULL);
	//strX.Format(_T("%f"), tmp->m_x);
	//strY.Format(_T("%f"), tmp->m_y);
	//strD.Format(_T("%f"), tmp->m_d);
	//strA.Format(_T("%f"), tmp->m_a);
	//strG.Format(_T("%f"), tmp->m_g);
	//strV.Format(_T("%f"), tmp->m_v);
	/*CString out = _T("X: ") + strX
		+ _T("\nY: ") + strY
		+ _T("\nV0: ") + strV
		+ _T("\nGravity: ") + strG
		+ _T("\nDuration: ") + strD
		+ _T("\nAngle: ") + strA;
	MessageBox(out);*/
	return TRUE;
}

void CDisplayPanel::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 1)
	{
		if (m_particle && m_particle->m_active)
		{
			m_particle->m_active = FALSE;
			for (int i = 0; i < MAXPARTICLES; i++)
			{
				if (m_particle->m_explosion[i].Active)
				{
					m_particle->m_active = TRUE;
					m_particle->UpdateParticleState(&m_particle->m_explosion[i], 100);
					//TRACE(L"Timer %d On!\n", i);
				}
			}
		}
		Invalidate();
	}

	CBasePanel::OnTimer(nIDEvent);
}


int CDisplayPanel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBasePanel::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CRect rcClient;
	GetClientRect(rcClient);

	m_pMemDC = new CDC();
	m_pMemBitmap = new CBitmap();

	CDC* pDC = GetDC();
	m_pMemDC->CreateCompatibleDC(pDC);
	m_pMemBitmap->CreateCompatibleBitmap(pDC, rcClient.Width(), rcClient.Height());
	m_pPreBitmap = m_pMemDC->SelectObject(m_pMemBitmap);

	m_pBkBrush = new CBrush(RGB(255, 255, 255));
	//m_hPrePen = (HPEN)m_pMemDC->SelectStockObject(BLACK_PEN);
	//m_hPreBrush = (HBRUSH)m_pMemDC->SelectStockObject(WHITE_BRUSH);

	ReleaseDC(pDC);

	return 0;
}

LRESULT CDisplayPanel::OnRefresh(WPARAM wParam, LPARAM lParam)
{
	if (m_particle)
	{
		delete m_particle;
		KillTimer(1);
	}
	m_particle = NULL;
	Invalidate();
	return TRUE;
}

void CDisplayPanel::OnDestroy()
{
	CBasePanel::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	KillTimer(1);
}


BOOL CDisplayPanel::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;
	//return CBasePanel::OnEraseBkgnd(pDC);
}

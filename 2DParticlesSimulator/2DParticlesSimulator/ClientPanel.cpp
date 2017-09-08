#include "stdafx.h"
#include "ClientPanel.h"

#define TIMER_DRAWPARTICLE	1


CClientPanel::CClientPanel()
{
	m_pPreBitmap = NULL;
	m_pMemBitmap = NULL;
	m_pMemDC = NULL;
}


CClientPanel::~CClientPanel()
{
	delete m_pMemBitmap;
	delete m_pMemDC;
	DeleteObject(m_hPenBk);
	DeleteObject(m_hBrushBk);
	//KillTimer(TIMER_DRAWPARTICLE);
}
BEGIN_MESSAGE_MAP(CClientPanel, CBasePanel)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()


int CClientPanel::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

	m_hPenBk = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	m_hBrushBk = CreateSolidBrush(RGB(255, 255, 255));

	InitializeParticles();

	SetTimer(TIMER_DRAWPARTICLE, 20, NULL);

	return 0;
}


BOOL CClientPanel::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;
	// return CBasePanel::OnEraseBkgnd(pDC);
}


void CClientPanel::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CBasePanel::OnPaint()
	CRect rcClient;
	GetClientRect(rcClient);

	dc.BitBlt(0, 0, rcClient.Width(), rcClient.Height(), m_pMemDC, 0, 0, SRCCOPY);
}

void CClientPanel::InitializeParticles()
{
	CRect rcClient;
	GetClientRect(rcClient);

	srand((unsigned)time(NULL));

	for (int i = 0; i < _MAX_NUM_UNITS; i++)
	{
		Units[i].m_vPosition.x = rand() / double(RAND_MAX) * (rcClient.Width() / 4.0 * 3.0) + rcClient.Width() / 8.0;
		Units[i].m_vPosition.y = rcClient.Height() - rand() / double(RAND_MAX) * (rcClient.Height() / 3.0);
	}

	for (int i = 0; i < _NUM_OBSTACLES; i++)
	{
		Obstacles[i].m_vPosition.x = rand() / double(RAND_MAX) * (rcClient.Width() / 4.0 * 3.0) + rcClient.Width() / 8.0;
		Obstacles[i].m_vPosition.y = rcClient.Height() - rand() / double(RAND_MAX) * (rcClient.Height() / 2.0) - rcClient.Height() / 2.0 + _OBSTACLE_RADIUS;
		Obstacles[i].m_fRadius = _OBSTACLE_RADIUS;
		Obstacles[i].m_fMass = 100.0;
	}
}

void CClientPanel::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == TIMER_DRAWPARTICLE)
	{
		CRect rcClient;
		GetClientRect(rcClient);

		DrawBkgnd();
		DrawObstacles();
		double dt = 0.2;

		for (int i = 0; i < _MAX_NUM_UNITS; i++)
		{
			Units[i].m_bCollision = CheckForCollisions(&Units[i]);
			Units[i].CalcLoads();
			Units[i].UpdateBodyEuler(dt);
			
			if (Units[i].m_vPosition.y < 0) Units[i].m_vPosition.y = 0.0;
			Units[i].Draw(m_pMemDC, rcClient.Height());
		}
		Invalidate();
	}

	CBasePanel::OnTimer(nIDEvent);
}

void CClientPanel::DrawBkgnd()
{
	CRect rcClient;
	GetClientRect(rcClient);

	HPEN hPrePen = (HPEN)m_pMemDC->SelectObject(m_hPenBk);
	HBRUSH hPreBrush = (HBRUSH)m_pMemDC->SelectObject(m_hBrushBk);

	m_pMemDC->Rectangle(rcClient);

	m_pMemDC->SelectObject(hPrePen);
	m_pMemDC->SelectObject(hPreBrush);
}

void CClientPanel::DrawObstacles()
{
	CRect rcClient;
	GetClientRect(rcClient);

	for (int i = 0; i < _NUM_OBSTACLES; i++)
	{
		Obstacles[i].Draw(m_pMemDC, rcClient.Height());
	}
}

bool CClientPanel::CheckForCollisions(CParticles* p)
{
	PhyVector n;
	PhyVector vr;
	float vrn;
	float j;
	PhyVector fi;
	bool hasCollision = false;

	p->m_vImpactForces.x = 0;
	p->m_vImpactForces.y = 0;

	if (p->m_vPosition.y <= (0 + p->m_fRadius))
	{
		n.x = 0;
		n.y = 1;
		vr = p->m_vVelocity;
		vrn = vr * n;

		if (vrn < 0.0)
		{
			j = -(vr * n) * (_RESTITUTION + 1) * p->m_fMass;
			fi = n;
			fi *= j / 0.2;
			p->m_vImpactForces += fi;

			p->m_vPosition.y = 0 + p->m_fRadius;
			p->m_vPosition.x = (0 + p->m_fRadius - p->m_vPrePosition.y) / (p->m_vPosition.y - p->m_vPrePosition.y) * (p->m_vPosition.x - p->m_vPrePosition.x) + p->m_vPrePosition.x;
			hasCollision = true;
		}
	}

	float r;
	PhyVector d;
	float s;

	for (int i = 0; i < _NUM_OBSTACLES; i++)
	{
		r = p->m_fRadius + Obstacles[i].m_fRadius;
		d = p->m_vPosition - Obstacles[i].m_vPosition;
		s = d.Magnitude() - r;

		if (s <= 0.0)
		{
			d.Normalize();
			n = d;
			vr = p->m_vVelocity - Obstacles[i].m_vVelocity;
			vrn = vr * n;

			if (vrn < 0.0)
			{
				j = -(vr * n) * (_RESTITUTION + 1) / (1 / p->m_fMass + 1 / Obstacles[i].m_fMass);
				fi = n;
				fi *= j / 0.2;
				p->m_vImpactForces += fi;

				p->m_vPosition -= n * s;
				hasCollision = true;
			}
		}
	}

	return hasCollision;
}
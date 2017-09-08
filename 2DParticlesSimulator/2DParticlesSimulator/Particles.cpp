#include "stdafx.h"
#include "Particles.h"



CParticles::CParticles()
{
	m_fMass = 1.0;
	m_vPosition.x = 0.0;
	m_vPosition.y = 0.0;
	m_vPosition.z = 0.0;
	m_vVelocity.x = 0.0;
	m_vVelocity.y = 0.0;
	m_vVelocity.z = 0.0;
	m_fSpeed = 0.0;
	m_vForces.x = 0.0;
	m_vForces.y = 0.0;
	m_vForces.z = 0.0;
	m_fRadius = 2.0;
	m_vGravity.x = 0;
	m_vGravity.y = m_fMass * _GRAVITYACCELERATION;
	m_vGravity.z = 0.0;
	m_hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	m_hBrush = CreateSolidBrush(RGB(0, 0, 0));
	m_vPrePosition.x = 0.0;
	m_vPrePosition.y = 0.0;
	m_vPrePosition.z = 0.0;
	m_vImpactForces.x = 0.0;
	m_vImpactForces.y = 0.0;
	m_vImpactForces.z = 0.0;
	m_bCollision = false;
}


CParticles::~CParticles()
{
	DeleteObject(m_hPen);
	DeleteObject(m_hBrush);
}

void CParticles::CalcLoads()
{
	m_vForces.x = 0.0f;
	m_vForces.y = 0.0f;

	if (m_bCollision)
	{
		m_vForces += m_vImpactForces;
	}
	else
	{
		// gravity
		m_vForces += m_vGravity;

		// drag
		PhyVector vDrag;
		float fDrag;

		vDrag = -m_vVelocity;
		vDrag.Normalize();
		// fDrag = 0.5 * density of fluid * speed of object ^ 2 * projected area of the object * drag coefficient
		fDrag = 0.5 * _AIRDENSITY * m_fSpeed * m_fSpeed * 3.14159 * m_fRadius * m_fRadius * _DRAGCOEFFICIENT;
		vDrag *= fDrag;
		m_vForces += vDrag;

		// wind
		PhyVector vWind;
		// fWind = 0.5 * density of fluid * speed of wind ^ 2 * prejected area of  the object * drag coefficient
		vWind.x = 0.5 * _AIRDENSITY * _WINDSPEED * _WINDSPEED * 3.14159 * m_fRadius * m_fRadius * _DRAGCOEFFICIENT;
		m_vForces += vWind;
	}
}

void CParticles::UpdateBodyEuler(double dt)
{
	PhyVector a;
	PhyVector dv;
	PhyVector ds;

	a = m_vForces / m_fMass;

	dv = a * dt;
	m_vVelocity += dv;

	ds = m_vVelocity * dt;
	m_vPosition += ds;

	m_fSpeed = m_vVelocity.Magnitude();
}

void CParticles::Draw(CDC* pDC, float wndh)
{
	HPEN hPrePen = (HPEN)pDC->SelectObject(m_hPen);
	HBRUSH hPreBrush = (HBRUSH)pDC->SelectObject(m_hBrush);

	CRect rcParticle;
	rcParticle.left = m_vPosition.x - m_fRadius;
	rcParticle.right = m_vPosition.x + m_fRadius;
	rcParticle.top = wndh - m_vPosition.y - m_fRadius;
	rcParticle.bottom = wndh - m_vPosition.y + m_fRadius;
	pDC->Ellipse(rcParticle);

	pDC->SelectObject(hPrePen);
	pDC->SelectObject(hPreBrush);
}


#pragma once
#include "PhyVector.h"


class CParticles
{
public:
	float m_fMass;
	PhyVector m_vPosition;
	PhyVector m_vVelocity;
	float m_fSpeed;
	PhyVector m_vForces;
	float m_fRadius;
	PhyVector m_vGravity;
	// collision
	PhyVector m_vPrePosition;
	PhyVector m_vImpactForces;
	bool m_bCollision;

	HPEN m_hPen;
	HBRUSH m_hBrush;

public:
	CParticles();
	~CParticles();
	void CalcLoads();
	void UpdateBodyEuler(double dt);
	void Draw(CDC* pDC, float wndh);
};


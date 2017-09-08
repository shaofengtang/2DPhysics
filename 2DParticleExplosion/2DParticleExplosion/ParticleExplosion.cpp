#include "stdafx.h"
#include "ParticleExplosion.h"

TParticleExplosion::TParticleExplosion()
{
	m_x = 0.0;
	m_y = 0.0;
	m_v0 = 0.0;
	m_duration = 0.0;
	m_gravity = 0.0;
	m_angle = 0.0;
	m_active = FALSE;
}

void TParticleExplosion::CreateParticleExplosion(float x, float y, float v, float duration, float gravity, float angle)
{
	m_active = TRUE;
	m_x = x;
	m_y = y;
	m_v0 = v;
	m_duration = duration;
	m_gravity = gravity;
	m_angle = angle;

	srand((unsigned)time(NULL));

	for (int i = 0; i < MAXPARTICLES; i++)
	{
		m_explosion[i].x = 0;
		m_explosion[i].y = 0;
		m_explosion[i].vi = rand() / double(RAND_MAX) * v / 2 + v / 2;

		if (angle < 999)
		{
			if (rand() / double(RAND_MAX) < 0.5)
				m_explosion[i].angle = -angle - (rand() % 11);
			else
				m_explosion[i].angle = -angle + (rand() % 11);
		}
		else
			m_explosion[i].angle = rand() % 361;

		m_explosion[i].life = rand() / double(RAND_MAX) * duration * 0.2 + duration * 0.8;
		m_explosion[i].r = (rand() % (255 - 225 + 1)) + 225; 
		m_explosion[i].g = 0; // (rand() % (115 - 85 + 1)) + 85;
		m_explosion[i].b = 0; // (rand() % (45 - 15 + 1)) + 15;
		m_explosion[i].time = 0;
		m_explosion[i].Active = TRUE;
		m_explosion[i].gravity = gravity;

	}
}

void TParticleExplosion::UpdateParticleState(TParticle* p, int dtime)
{
	float t;

	p->time += dtime;
	t = (float)p->time / 1000.0f;
	p->x = p->vi * cos(p->angle * PI / 180.0f) * t;
	p->y = p->vi * sin(p->angle * PI / 180.0f) * t + 0.5f * p->gravity * t * t;
	p->r = (float)(p->life - p->time) / (float)p->life * p->r;
	p->g = (float)(p->life - p->time) / (float)p->life * p->g;
	p->b = (float)(p->life - p->time) / (float)p->life * p->b;
	
	if (p->time >= p->life) p->Active = FALSE;
}
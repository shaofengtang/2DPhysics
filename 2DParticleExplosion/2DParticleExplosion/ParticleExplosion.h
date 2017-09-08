#pragma once

#define MAXPARTICLES 100

typedef struct _Packet
{
	float m_x;
	float m_y;
	float m_v;
	float m_g;
	float m_a;
	float m_d;
	_Packet(float x, float y, float v, float g, float a, float d) : m_x(x), m_y(y), m_v(v), m_g(g), m_a(a), m_d(d) {}
} MessagePacket;

typedef struct _TParticle
{
	float x;
	float y;
	float vi;
	float angle;
	int life;
	int r;
	int g;
	int b;
	int time;
	float gravity;
	bool Active;
} TParticle;

class TParticleExplosion
{
public:
	TParticle m_explosion[MAXPARTICLES];
	float m_v0;
	float m_x;
	float m_y;
	float m_gravity;
	float m_angle;
	float m_duration;
	BOOL m_active;

	TParticleExplosion();
	void CreateParticleExplosion(float x, float y, float v, float duration, float gravity, float angle);
	void UpdateParticleState(TParticle* p, int dtime);
};

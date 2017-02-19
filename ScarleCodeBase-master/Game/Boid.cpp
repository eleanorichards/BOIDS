#include "Boid.h"
#include "GameData.h"

Boid::Boid(string _fileName, ID3D11Device * _pd3dDevice, IEffectFactory * _EF) : CMOGO(_fileName, _pd3dDevice, _EF)
{
	//initialise as not alive
	m_alive = false;
}

Boid::~Boid()
{
}

void Boid::Spawn(Vector3 _pos, Vector3 _scale, Vector3 _dir)
{
	m_alive = true; // turn this enemy ON
	m_pos = _pos;
	m_scale = _scale;
	m_dir = _dir;
}

void Boid::Tick(GameData * _GD)
{
	if (m_alive)
	{
		//Vec3 m_pos += m_dir (set to travelDirection in boids manager)
		m_pos += m_dir * _GD->m_dt;
	}
	CMOGO::Tick(_GD);
}

void Boid::Draw(DrawData * _DD)
{
	if (m_alive)
	{
		CMOGO::Draw(_DD);
	}
}

void Boid::SetAlive(bool isAlive)
{
	m_alive = isAlive;
}

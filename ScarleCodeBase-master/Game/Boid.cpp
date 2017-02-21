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
		m_pos += (m_vel + m_dir) * _GD->m_dt; //(m_dir is set to travelDirection in boids manager)
		//+= m_vel in boidsmanager
		//m_pos += m_vel * _GD->m_dt;
		///Bounding Box
	/*	if (m_pos.x >= 50 )
		{
			m_dir.x *= -1;
		}
		if (m_pos.x <= 50)
		{
			m_dir.x *= -1;
		}
		if (m_pos.y >= 50)
		{
			m_dir.y *= -1;
		}
		if (m_pos.y <= -50)
		{
			m_dir.y *= -1;
		}*/
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

void Boid::setVelocity(Vector3 velocity)
{
	m_vel = velocity;
}

void Boid::setPosition(Vector3 position)
{
	m_pos = position;
}

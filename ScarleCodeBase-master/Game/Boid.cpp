#include "Boid.h"
#include "GameData.h"

Boid::Boid(string _fileName, ID3D11Device * _pd3dDevice, IEffectFactory * _EF) : CMOGO(_fileName, _pd3dDevice, _EF)
{

}

Boid::~Boid()
{
}

void Boid::Spawn(Vector3 _pos, Vector3 _scale, Vector3 _dir)
{
	m_alive = true; // turn this enemy ON
	m_pos = _pos;
	m_scale = _scale;
	//m_dir = _dir;
	travelDirection = _dir;

}

void Boid::Tick(GameData * _GD)
{
	if (m_alive)
	{
		//set random travel direction
		
		//do all your enemy things (AI etc)
		m_pos += travelDirection * _GD->m_dt;

		Matrix scaleMat = Matrix::CreateScale(m_scale);
		m_worldMat = m_fudge * scaleMat;
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

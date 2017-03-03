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
	//set random direction every few seconds
	if (_GD->m_dt * 0.2 > ((float)rand() / (float)RAND_MAX))
	{
		//very erratic start movemtn is because of large travelDirection

		randomDirection = Vector3(((float)(rand() % max) - min), ((float)(rand() % max) - min), (((float)(rand() % max) - min)))*0.01;
	}
	if (m_alive)
	{
		if (m_pos.x >= 100 || m_pos.x <= -100 || m_pos.y >= 100 || m_pos.y <= -100 || m_pos.z >= 100 || m_pos.z <= -100)
		{
			//move to opposite end of box
			//CHANGE this currently moves all boids to the exact same point 
			inBoundingBox = false;	
			m_pos *= (-1);
			//m_pos = m_vel == Vector3() ? Vector3() : Vector3();
		}
		else
		{
			inBoundingBox = true;
		}
		if (inBoundingBox)
		{
			//need a better random mechanic  + randomDirection
			setAcceleration(((m_vel)+randomDirection) * _GD->m_dt);
			m_pos += acceleration;//(m_dir is set to travelDirection in boids manager)
			//m_yaw += m_pos;
		}
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

//limit and then set velocity
void Boid::setVelocity(Vector3 velocity)
{
	
	m_vel = velocity;
}

void Boid::setPosition(Vector3 position)
{
	m_pos = position;
}

void Boid::setRotation(float yaw, float pitch)
{
	m_yaw = yaw;
	//m_pitch = pitch;
}

void Boid::setAcceleration(Vector3 _acceleration)
{
	
	if (_acceleration.x > maxAcceleration)
	{
		_acceleration.x = maxAcceleration;
	}
	if (_acceleration.y > maxAcceleration)
	{
		_acceleration.y = maxAcceleration;
	}
	if (_acceleration.z > maxAcceleration)
	{
		_acceleration.z = maxAcceleration;
	}
	if (_acceleration.x < minAcceleration)
	{
		_acceleration.x = minAcceleration;
	}
	if (_acceleration.y < minAcceleration)
	{
		_acceleration.y = minAcceleration;
	}
	if (_acceleration.z < minAcceleration)
	{
		_acceleration.z = minAcceleration;
	}

	acceleration = _acceleration;
}

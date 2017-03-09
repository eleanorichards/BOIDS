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

void Boid::Spawn(Vector3 _pos, Vector3 _scale, Vector3 _dir, GameData* _GD)
{
	//set random direction every few seconds

	
	initialDirection = Vector3(((float)(rand() % max) - min), ((float)(rand() % max) - min), (((float)(rand() % max) - min)))*0.1;
	
	m_alive = true; // turn this enemy ON
	m_pos = _pos;
	m_scale = _scale;
	m_vel = initialDirection;
}

void Boid::Tick(GameData * _GD)
{

	if (m_alive)
	{
		if (m_pos.x >= 500 || m_pos.x <= -500 || m_pos.y >= 500 || m_pos.y <= -500 || m_pos.z >= 500 || m_pos.z <= -500)
		{
			//move to opposite end of box
			//CHANGE this currently moves all boids to the exact same point 
			m_pos *= (-1);
			//m_pos = m_vel == Vector3() ? Vector3() : Vector3();
		}
		else 
		{
			
			setAcceleration(((m_vel)) * _GD->m_dt);
			
			m_pos += acceleration;//(m_dir is set to travelDirection in boids manager)
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

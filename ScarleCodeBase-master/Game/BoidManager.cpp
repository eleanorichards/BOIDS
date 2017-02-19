#include "BoidManager.h"

BoidManager::BoidManager(int _numOfBoids, string _modelFileName, ID3D11Device * _pd3dDevice, IEffectFactory * _EF)
{
	for (int i = 0; i < _numOfBoids; i++)
	{
		m_Boids.push_back(new Boid(_modelFileName, _pd3dDevice, _EF));
	}
	initialLocation = Vector3(0.0f, 0.0f, 0.0f);
	travelDirection = Vector3(((rand() % max - min) + min), 0.0f, ((rand() % max - min) + min));

}

BoidManager::~BoidManager()
{
}

void BoidManager::Tick(GameData * _GD)
{
	for (list<Boid*>::iterator it = m_Boids.begin(); it != m_Boids.end(); it++)
	{
		if (!(*it)->isAlive())
		{
			(*it)->Spawn(initialLocation, Vector3::One, travelDirection);
			break;
		}
	}
}

void BoidManager::Draw(DrawData * _DD)
{
	for (list<Boid*>::iterator it = m_Boids.begin(); it != m_Boids.end(); it++)
	{
		(*it)->Draw(_DD);
	}
}

list<Boid*> BoidManager::GetBoid()
{
	return m_Boids;
}

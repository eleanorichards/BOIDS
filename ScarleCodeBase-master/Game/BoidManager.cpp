#include "BoidManager.h"
#include <dinput.h>
#include "GameData.h"

BoidManager::BoidManager(int _numOfBoids, string _modelFileName, ID3D11Device * _pd3dDevice, IEffectFactory * _EF)
{
	//boids.reserve(50);
	//boids.assign(_numOfBoids, Boid(_modelFileName, _pd3dDevice, _EF));
	for (int i = 0; i < _numOfBoids; i++)
	{
		m_Boids.push_back(new Boid(_modelFileName, _pd3dDevice, _EF));
		initialLocation = Vector3(((rand() % max - min) + min), ((rand() % max - min) + min), ((rand() % max - min) + min));
		travelDirection = Vector3(((rand() % max - min) + min), ((rand() % max - min) + min), ((rand() % max - min) + min));
	}
	//for (auto& iter = m_Boids.begin(); iter != m_Boids.end(); iter++)
	//{
	//	m_Boids.push_back(new Boid(_modelFileName, _pd3dDevice, _EF));
	//}
}

BoidManager::~BoidManager()
{
}

void BoidManager::Tick(GameData * _GD)
{
	//Spawn in boids
	for (list<Boid*>::iterator it = m_Boids.begin(); it != m_Boids.end(); it++)
	{
	//for (auto& it = m_Boids.begin(); it != boids.end(); it++)
	//{
		if (!(*it)->isAlive())
		{
			(*it)->Spawn(initialLocation, Vector3::One, travelDirection);
			break;
		}
		(*it)->Tick(_GD);
		moveBoid(*it);
	}
	//Get user input for new boids
	getUserInput(_GD);
}

void BoidManager::Draw(DrawData * _DD)
{
	//for (auto& it = boids.begin(); it != boids.end(); it++)
	for (list<Boid*>::iterator it = m_Boids.begin(); it != m_Boids.end(); it++)
	{
		(*it)->Draw(_DD);
	}
}

void BoidManager::getUserInput(GameData * _GD)
{
	if (_GD->m_keyboardState[DIK_A] & 0x80)
	{
		float mouseX = _GD->m_mouseState->lX;
		float mouseY = _GD->m_mouseState->lY;
		initialLocation = Vector3(mouseX, mouseY, 0.0f);
	}
}

void BoidManager::moveBoid(Boid* _boid)
{
	Vector3 v1, v2, v3;

	for (list<Boid*>::iterator it = m_Boids.begin(); it != m_Boids.end(); it++)
	{
		v1 = cohesion(_boid);
		v2 = separation(_boid);
		v3 = alignment(_boid);

		_boid->setVelocity((_boid->getVelocity() + v1 + v2 + v3) / velocityModifier);
		//_boid->SetPos(_boid->GetPos() + _boid->getVelocity());
	}
}

//not going too close to other boids
Vector3 BoidManager::separation(Boid* _boid)
{
	//please think of a better name for this
	Vector3 c;
	for (list<Boid*>::iterator it = m_Boids.begin(); it != m_Boids.end(); it++)
	{
		if (*it != _boid)
		{
			//if distance between is below 50
			if (Vector3::Distance((*it)->GetPos(), _boid->GetPos()) < 25)
			{
				c = c - ((*it)->GetPos() - _boid->GetPos());
			}
		}
	}
	return c;
}

//aligning velocity with other boids
Vector3 BoidManager::alignment(Boid* _boid)
{
	Vector3 pvj;
	int boidNumber = 0;

	for (list<Boid*>::iterator it = m_Boids.begin(); it != m_Boids.end(); it++)
	{
		if (*it != _boid)
		{
			pvj += (*it)->getVelocity();
		}
		boidNumber++;
	}
	pvj = pvj / (boidNumber - 1);

	return ((pvj - _boid->getVelocity()) / 8);
}

//towards the average mass of other boids
Vector3 BoidManager::cohesion(Boid* _boid)
{
	Vector3 percievedCentre;
	int boidNumber = 0;

	for (list<Boid*>::iterator it = m_Boids.begin(); it != m_Boids.end(); it++)
	{
		//(*it)->GetPos();
		if (*it != _boid)
		{
			percievedCentre += (*it)->GetPos();
			boidNumber++;
		}
	}
	percievedCentre = percievedCentre / boidNumber;

	return ((percievedCentre - _boid->GetPos()) / 100);
}

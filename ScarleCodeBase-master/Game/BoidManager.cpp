#include "BoidManager.h"
#include <dinput.h>
#include "GameData.h"

BoidManager::BoidManager(int _numOfBoids, string _modelFileName, ID3D11Device * _pd3dDevice, IEffectFactory * _EF)
{
	for (int i = 0; i < _numOfBoids; i++)
	{
		m_Boids.push_back(new Boid(_modelFileName, _pd3dDevice, _EF));
	}
}

BoidManager::~BoidManager()
{
}

void BoidManager::Tick(GameData * _GD)
{
	getUserInput(_GD);
	//Spawn in boids
	for (list<Boid*>::iterator it = m_Boids.begin(); it != m_Boids.end(); it++)
	{
		if (!(*it)->isAlive() && placeBoid && it != m_Boids.end())
		{
			travelDirection = Vector3(((rand() % max - min) + min), ((rand() % max - min) + min), ((rand() % max - min) + min));
			(*it)->Spawn(initialLocation, Vector3::One, travelDirection);
			placeBoid = false;
			boidsInScene ++;
			break;
		}
		(*it)->Tick(_GD);
		moveBoid(*it);
	}
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
	if (_GD->m_mouseState->rgbButtons[0] && placeBoid == false)
	{
		float mouseX = _GD->m_mouseState->lX;
		float mouseY = _GD->m_mouseState->lY;
		initialLocation = Vector3(mouseX, mouseY, 0.0f);
		placeBoid = true;
		numOfBoids++;
	}
	
		
}


void BoidManager::moveBoid(Boid* _boid)
{
	Vector3 v1, v2, v3;

	for (list<Boid*>::iterator it = m_Boids.begin(); it != m_Boids.end(); it++)
	{
		if (*it != _boid)
		{
			v1 = cohesion(_boid);
			v2 = separation(_boid);
			v3 = alignment(_boid);

			_boid->setVelocity((_boid->getVelocity() + v1 + v2 + v3) / velocityModifier);
			//_boid->setRotation(v1.x, v1.y);
			//_boid->SetPos(_boid->GetPos() + _boid->getVelocity());
		}
	}
}

//not going too close to other boids
Vector3 BoidManager::separation(Boid* _boid)
{
	//please think of a better name for this
	Vector3 c;
	for (list<Boid*>::iterator it = m_Boids.begin(); it != m_Boids.end(); it++)
	{
		if (*it != _boid )
		{
			//if distance between is below proximity
			if (Vector3::Distance((*it)->GetPos(), _boid->GetPos()) < proximity)
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
	int x = 0;

	for (list<Boid*>::iterator it = m_Boids.begin(); it != m_Boids.end(); it++)
	{
		if (*it != _boid )
		{
			pvj += (*it)->getVelocity();
		}
		x++;
	}
	pvj = pvj / (x - 1);
	//find out what 8 is
	return ((pvj - _boid->getVelocity()) / 5);
}

//towards the average mass of other boids
Vector3 BoidManager::cohesion(Boid* _boid)
{
	Vector3 percievedCentre;
	int y = 0;
	for (list<Boid*>::iterator it = m_Boids.begin(); it != m_Boids.end(); it++)
	{
		//(*it)->GetPos();
		if (*it != _boid)
		{
			percievedCentre += (*it)->GetPos();
			//boidNumber++;
			y++;
		}
	}
	percievedCentre = percievedCentre / y;

	return ((percievedCentre - _boid->GetPos()) / 10);
}

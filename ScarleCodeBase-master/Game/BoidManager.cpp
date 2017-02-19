#include "BoidManager.h"
#include <dinput.h>
#include "GameData.h"

BoidManager::BoidManager(int _numOfBoids, string _modelFileName, ID3D11Device * _pd3dDevice, IEffectFactory * _EF)
{
	
	boids.reserve(50);
	boids.assign(_numOfBoids, Boid(_modelFileName, _pd3dDevice, _EF));

	for (auto& iter = boids.begin(); iter != boids.end(); iter++)
	{
		m_Boids.push_back(new Boid(_modelFileName, _pd3dDevice, _EF));

	}
	/*for (int i = 0; i < _numOfBoids; i++)
	{
		m_Boids.push_back(new Boid(_modelFileName, _pd3dDevice, _EF));
	}*/
	initialLocation = Vector3(0.0f, 0.0f, 0.0f);
	travelDirection = Vector3(((rand() % max - min) + min), ((rand() % max - min) + min), ((rand() % max - min) + min));

}

BoidManager::~BoidManager()
{
}

void BoidManager::Tick(GameData * _GD)
{
	//Spawn in boids
	/*for (list<Boid*>::iterator it = m_Boids.begin(); it != m_Boids.end(); it++)
	{*/
	for (auto& it = boids.begin(); it != boids.end(); it++)
	{
		if (!(it)->isAlive())
		{
			(it)->Spawn(initialLocation, Vector3::One, travelDirection);
			break;
		}
		(it)->Tick(_GD);
	}
	//}

	//Get user input for new boids
	getUserInput(_GD);
}

void BoidManager::Draw(DrawData * _DD)
{
	//for (list<Boid*>::iterator it = m_Boids.begin(); it != m_Boids.end(); it++)
	for (auto& it = boids.begin(); it != boids.end(); it++)
	{
		(it)->Draw(_DD);
	}
}

//list<Boid*> BoidManager::GetBoid()
//{
//	return m_Boids;
//}

void BoidManager::getUserInput(GameData * _GD)
{
	if (_GD->m_keyboardState[DIK_A] & 0x80)
	{
		float mouseX = _GD->m_mouseState->lX;
		float mouseY = _GD->m_mouseState->lY;
		initialLocation = Vector3(mouseX, mouseY, 0.0f);
	}
}

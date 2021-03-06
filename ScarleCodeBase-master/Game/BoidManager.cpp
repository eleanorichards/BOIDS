#include "BoidManager.h"
#include <dinput.h>
#include "GameData.h"
#include <sstream>
#include "TextGO2D.h"
#include "DrawData2D.h"
#include <iostream>
#include <stdio.h>

BoidManager::BoidManager(int _numOfBoids, ID3D11Device * _pd3dDevice)
{
	for (int i = 0; i < _numOfBoids; i++)
	{
		m_Boids.push_back(new Boid(_pd3dDevice));
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
			(*it)->Spawn(initialLocation, 0.2*Vector3::One, travelDirection, _GD);
			placeBoid = false;
		}
		if ((*it)->isAlive())
		{
			(*it)->Tick(_GD);
			moveBoid((*it), _GD);
		}
	}
}

void BoidManager::Draw(DrawData * _DD)
{
	//for (auto& it = boids.begin(); it != boids.end(); it++)
	for (list<Boid*>::iterator it = m_Boids.begin(); it != m_Boids.end(); it++)
	{
		if((*it)->isAlive())
		(*it)->Draw(_DD);
	}
}

void BoidManager::getUserInput(GameData * _GD)
{
	if (_GD->m_keyboardState[DIK_Q] && placeBoid == false)
	{
		initialLocation = Vector3(((float)(rand() % startMax) - startMin), ((float)(rand() % startMax) - startMin), (((float)(rand() % startMax) - startMin)));
		boidsInScene++;
		placeBoid = true;
	}
	if (alignmentModifier >= 1 || separationModifier >= -1 || cohesionModifier >= -1)
	{

		if (_GD->m_keyboardState[DIK_1] && !(_GD->m_prevKeyboardState[DIK_1]))
			alignmentModifier -= 0.5f;
		else if (_GD->m_keyboardState[DIK_2] && !(_GD->m_prevKeyboardState[DIK_2]))
			alignmentModifier += 0.5f;
		else if (_GD->m_keyboardState[DIK_3] && !(_GD->m_prevKeyboardState[DIK_3]))
			proximity -= 0.5f;
		else if (_GD->m_keyboardState[DIK_4] && !(_GD->m_prevKeyboardState[DIK_4]))
			proximity += 0.5f;
		else if (_GD->m_keyboardState[DIK_5] && !(_GD->m_prevKeyboardState[DIK_5]))
			cohesionModifier -= 0.5f;
		else if (_GD->m_keyboardState[DIK_6] && !(_GD->m_prevKeyboardState[DIK_6]))
			cohesionModifier += 0.5f;
	}
}

/*	....................................
	Cycle through every boid on screen
	Apply boid-like change in velocity for 90% of frames 
	....................................
*/
void BoidManager::moveBoid(Boid* _boid, GameData * _GD)
{
	Vector3 v1, v2, v3;

	for (list<Boid*>::iterator it = m_Boids.begin(); it != m_Boids.end(); it++)
	{
		if (*it != _boid && (*it)->isAlive())
		{
			v1 = cohesion(_boid) * _GD->m_dt;
			v2 = separation(_boid) * _GD->m_dt;
			v3 = alignment(_boid) * _GD->m_dt;
			/*if (_GD->m_dt * 0.9 > ((float)rand() / (float)RAND_MAX))
			{*/
			Vector3 velly = _boid->getVelocity();

			_boid->setVelocity(velly + v1 + v2 + v3);
			//}
		}
	}
}

//towards the centre of mass of other boids
Vector3 BoidManager::cohesion(Boid* _boid)
{
	Vector3 boid_position = _boid->GetPos();
	Vector3 boid_velocity = _boid->getVelocity();

	Vector3 percievedCentre = Vector3::Zero;
	int count = 0;
	for (list<Boid*>::iterator it = m_Boids.begin(); it != m_Boids.end(); it++)
	{
		if (*it != _boid && (*it)->isAlive())
		{
			//float d = Vector3::DistanceSquared((*it)->GetPos(), _boid->GetPos());
			//if (d > 0 && d < searchRadius)
			//{
				percievedCentre += ((*it)->GetPos());
				count++;
			//}
		}
		
	}
	if (boidsInScene > 0)
	{
		percievedCentre /= boidsInScene;

		return seek(percievedCentre, boid_position, boid_velocity);
	}
	else
	{
		return Vector3::Zero;
	}
}

Vector3 BoidManager::seek(Vector3 _target, Vector3 _pos, Vector3 _vel)
{
	float maxSpeed = 1.0f;
	float maxForce = 1.0f;
	Vector3 pos = _pos;
	Vector3 vel = _vel;
	Vector3 target = _target - pos;
	//target.Normalize();
	target *= maxSpeed;
	target -= _vel;
	//target = XMVector3ClampLength(target, 0.0f, maxSpeed);

	Vector3 seek = target - _vel;

	std::cout << "target" << target.x << target.y << target.z << "\n";

	std::cout << "Seek1" << seek.x << seek.y << seek.z << "\n";

	//seek = XMVector3ClampLength(seek, 0.0f, maxForce);
	return seek;
}

//not going too close to other boids
Vector3 BoidManager::separation(Boid* _boid)
{
	Vector3 c;
	for (list<Boid*>::iterator it = m_Boids.begin(); it != m_Boids.end(); it++)
	{
		if (*it != _boid && (*it)->isAlive())
		{
			//if distance between is below proximity
			if (Vector3::DistanceSquared((*it)->GetPos(), _boid->GetPos()) < proximity)
			{
				c -= ((*it)->GetPos() - _boid->GetPos());
			}
		}
	}
	return c;
}

//aligning velocity with other boids
Vector3 BoidManager::alignment(Boid* _boid)
{
	Vector3 pvj;
	for (list<Boid*>::iterator it = m_Boids.begin(); it != m_Boids.end(); it++)
	{
		if (*it != _boid && (*it)->isAlive())
		{
			//if (Vector3::DistanceSquared((*it)->GetPos(), _boid->GetPos()) < searchRadius + 10)
			//{
				pvj += ((*it)->getVelocity());
			//}
		}
	}
	pvj = pvj / (boidsInScene - 1);
	//Alignment modifier
	return ((pvj - _boid->getVelocity()) / alignmentModifier);
}


std::string BoidManager::getNumOfBoidsAsString()
{
	std::stringstream bString;
	bString << boidsInScene;
	return bString.str();
}

std::string BoidManager::getAlignmentAsString()
{
	std::stringstream aString;
	aString << alignmentModifier;
	return aString.str();
}


std::string BoidManager::getSeparationAsString()
{
	std::stringstream bString;
	bString << proximity;
	return bString.str();
}


std::string BoidManager::getCohesionAsString()
{
	std::stringstream cString;
	cString << cohesionModifier;
	return cString.str();
}

void BoidManager::DrawScreenSpace(DrawData2D* _DD2D)
{
	TextGO2D boidNumText("Boids: (Q)" + getNumOfBoidsAsString() + "\nAlignment (1-2): " + getAlignmentAsString() + "\nSeparation (3-4): " + getSeparationAsString() + "\nCohesion (5-6): " + getCohesionAsString());
	boidNumText.SetPos(Vector2(0.0f, 60.0f));
	boidNumText.SetColour(Color((float*)&DirectX::Colors::Green));
	boidNumText.SetScale(0.4f);
	boidNumText.Draw(_DD2D);	
}

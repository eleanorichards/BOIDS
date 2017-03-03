#include "BoidManager.h"
#include <dinput.h>
#include "GameData.h"
#include <sstream>
#include "TextGO2D.h"
#include "DrawData2D.h"

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
		}
		(*it)->Tick(_GD);
		moveBoid(*it, _GD);
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
		boidsInScene++;
		placeBoid = true;
	}
	if (_GD->m_keyboardState[DIK_K])
	{

	}
		
}


void BoidManager::moveBoid(Boid* _boid, GameData * _GD)
{
	Vector3 v1, v2, v3;

	for (list<Boid*>::iterator it = m_Boids.begin(); it != m_Boids.end(); it++)
	{
		if (*it != _boid)
		{
			v1 = cohesion(_boid, _GD)  *_GD->m_dt;
			v2 = separation(_boid, _GD) *_GD->m_dt;
			v3 = alignment(_boid, _GD) *_GD->m_dt;

			_boid->setVelocity((_boid->getVelocity() + v1 + v2 + v3) );
			//_boid->setRotation(v1.x, v1.y);
			//_boid->SetPos(_boid->GetPos() + _boid->getVelocity());
		}
	}
}

//not going too close to other boids
Vector3 BoidManager::separation(Boid* _boid, GameData * _GD)
{
	Vector3 c;
	for (list<Boid*>::iterator it = m_Boids.begin(); it != m_Boids.end(); it++)
	{
		if (*it != _boid )
		{
			//if distance between is below proximity
			if (Vector3::Distance((*it)->GetPos(), _boid->GetPos()) < proximity)
			{
				c -= ((*it)->GetPos() - _boid->GetPos());
			}
		}
	}
	//seperation modifier
	return c * separationModifier;
}

//aligning velocity with other boids
Vector3 BoidManager::alignment(Boid* _boid, GameData * _GD)
{
	Vector3 pvj;
	int x = 0;

	for (list<Boid*>::iterator it = m_Boids.begin(); it != m_Boids.end(); it++)
	{
		if (*it != _boid )
		{
			if (Vector3::DistanceSquared((*it)->GetPos(), _boid->GetPos()) < 1)
			{
				pvj += ((*it)->getVelocity())  * _GD->m_dt;
			}
		}
		x++;
	}
	pvj = pvj / (x - 1);
	//Alignment modifier
	return ((pvj - _boid->getVelocity()) / alignmentModifier);
}

//towards the average mass of other boids
Vector3 BoidManager::cohesion(Boid* _boid, GameData * _GD)
{
	Vector3 percievedCentre;
	int y = 0;
	for (list<Boid*>::iterator it = m_Boids.begin(); it != m_Boids.end(); it++)
	{
		//(*it)->GetPos();
		if (*it != _boid)
		{
			percievedCentre += ((*it)->GetPos()) * _GD->m_dt;
			//boidNumber++;
			y++;
		}
	}
	percievedCentre = percievedCentre / y;
	//Cohesion modifier
	return ((percievedCentre - _boid->GetPos()) / cohesionModifier);
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
	bString << separationModifier;
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
	TextGO2D boidNumText("Boids: " + getNumOfBoidsAsString() + "\nAlignment: " + getAlignmentAsString() + "\nSeparation: " + getSeparationAsString() + "\nCohesion: " + getCohesionAsString());
	boidNumText.SetPos(Vector2(0.0f, 60.0f));
	boidNumText.SetColour(Color((float*)&DirectX::Colors::Green));
	boidNumText.SetScale(0.4f);
	boidNumText.Draw(_DD2D);	
}

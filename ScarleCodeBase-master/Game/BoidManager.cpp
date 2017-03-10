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
	if (_GD->m_mouseState->rgbButtons[0] * _GD->m_dt && placeBoid == false)
	{
		initialLocation = Vector3(((float)(rand() % max) - min), ((float)(rand() % max) - min), (((float)(rand() % max) - min)));
		boidsInScene++;
		placeBoid = true;
	}
	if (alignmentModifier >= 1 || separationModifier >= -1 || cohesionModifier >= -1)
	{

		if (_GD->m_keyboardState[DIK_1] * _GD->m_dt)
			alignmentModifier -= 0.5f;
		if (_GD->m_keyboardState[DIK_2] * _GD->m_dt)
			alignmentModifier += 0.5f;
		if (_GD->m_keyboardState[DIK_3] * _GD->m_dt)
			proximity -= 0.5f;
		if (_GD->m_keyboardState[DIK_4] * _GD->m_dt)
			proximity += 0.5f;
		if (_GD->m_keyboardState[DIK_5] * _GD->m_dt)
			cohesionModifier -= 0.5f;
		if (_GD->m_keyboardState[DIK_6] * _GD->m_dt)
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
		if (*it != _boid & (*it)->isAlive())
		{
			v1 = cohesion(_boid) * _GD->m_dt;
			v2 = separation(_boid) * _GD->m_dt;
			v3 = alignment(_boid) * _GD->m_dt;

			
			_boid->setVelocity((_boid->getVelocity() + v1 + v2 + v3) );
		}
	}
}

//towards the centre of mass of other boids
Vector3 BoidManager::cohesion(Boid* _boid)
{
	Vector3 percievedCentre;
	for (list<Boid*>::iterator it = m_Boids.begin(); it != m_Boids.end(); it++)
	{
		//(*it)->GetPos();
		if (*it != _boid && (*it)->isAlive())
		{
			percievedCentre += ((*it)->GetPos());
		}
	}
	percievedCentre = percievedCentre / boidsInScene;
	//Cohesion modifier
	return ((percievedCentre - _boid->GetPos()) / cohesionModifier);
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
Vector3 BoidManager::alignment(Boid* _boid)
{
	Vector3 pvj;
	for (list<Boid*>::iterator it = m_Boids.begin(); it != m_Boids.end(); it++)
	{
		if (*it != _boid && (*it)->isAlive())
		{
			if (Vector3::DistanceSquared((*it)->GetPos(), _boid->GetPos()) < 100)
			{
				pvj += ((*it)->getVelocity());
			}
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
	TextGO2D boidNumText("Boids: " + getNumOfBoidsAsString() + "\nAlignment (1-2): " + getAlignmentAsString() + "\nSeparation (3-4): " + getSeparationAsString() + "\nCohesion (5-6): " + getCohesionAsString());
	boidNumText.SetPos(Vector2(0.0f, 60.0f));
	boidNumText.SetColour(Color((float*)&DirectX::Colors::Green));
	boidNumText.SetScale(0.4f);
	boidNumText.Draw(_DD2D);	
}

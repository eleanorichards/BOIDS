#pragma once
#include "gameobject.h"
#include <string>
#include "Model.h"
#include "Boid.h"
#include <list>
#include <vector>

using namespace std;
using namespace DirectX;	

class BoidManager : public GameObject
{
public:
	BoidManager(int _numOfBoids, string _modelFileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF);
	~BoidManager();
	//void checkForCollisions(GameData* _GD);
	virtual void Tick(GameData* _GD) override;
	virtual void Draw(DrawData* _DD) override;
	//list<Boid*> GetBoid();
	void getUserInput(GameData * _GD);
	

private:
	using BoidVec = vector<Boid>;
	BoidVec boids;
	list<Boid*> m_Boids;
	Vector3 initialLocation;
	Vector3 travelDirection;
	//vector<Boid> boids;
	int max = 100;
	int min = -100;
};
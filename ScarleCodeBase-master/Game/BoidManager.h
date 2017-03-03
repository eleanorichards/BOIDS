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
	virtual void Tick(GameData* _GD) override;
	virtual void Draw(DrawData* _DD) override;
	virtual void DrawScreenSpace(DrawData2D* _DD2D);

	void getUserInput(GameData * _GD);
	void moveBoid(Boid* _boid, GameData * _GD);

	Vector3 separation(Boid* _boid, GameData * _GD);
	Vector3 alignment(Boid* _boid, GameData * _GD);
	Vector3 cohesion(Boid* _boid, GameData * _GD);


	//GETTERS
	int getNumOfBoids() { return numOfBoids; }
	
	std::string getNumOfBoidsAsString();
	std::string getAlignmentAsString();
	std::string getSeparationAsString();
	std::string getCohesionAsString();




	//SETTERS
	void setNumOfBoids(int _numOfBoids) { numOfBoids = _numOfBoids; }

private:
	list<Boid*> m_Boids;
	Boid* _Boid;

	Vector3 initialLocation;
	Vector3 travelDirection;
	Vector3 randomDirection;

	float alignmentModifier = 2;
	float separationModifier = 1;
	float cohesionModifier = 15;
	int numOfBoids = 0;
	int proximity = 20;
	int max = 10;
	int min = -10;
	int boidsInScene = 0;
	bool placeBoid = false;
};
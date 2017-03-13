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
	BoidManager(int _numOfBoids, ID3D11Device* _pd3dDevice);
	~BoidManager();
	virtual void Tick(GameData* _GD) override;
	virtual void Draw(DrawData* _DD) override;
	virtual void DrawScreenSpace(DrawData2D* _DD2D);

	void getUserInput(GameData * _GD);
	void moveBoid(Boid* _boid, GameData * _GD);

	Vector3 separation(Boid* _boid);
	Vector3 alignment(Boid* _boid);
	Vector3 cohesion(Boid* _boid);

	Vector3 seek(Vector3 _target);

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

	//Vector3 percievedCentre;

	float alignmentModifier = 1;
	float separationModifier = 1;
	float cohesionModifier = 8;
	float searchRadius = 500;
	float proximity = 20;

	int numOfBoids = 0;
	int max = 10;
	int min = -10;
	int startMax = -50;
	int startMin = 100;
	int boidsInScene = 0;
	int menuChoice = 0;
	bool placeBoid = false;

};
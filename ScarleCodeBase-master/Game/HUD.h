#pragma once
#include "gameobject.h"
#include <string>
#include "BoidManager.h"
#include "DrawData.h"


using namespace DirectX;

class HUD : public GameObject
{
public:
	HUD();
	~HUD();

	//virtual void Draw(DrawData* _DD) override;


	std::string getNumOfBoidsAsString();

private:
	std::string currentBoidsString;
	BoidManager* pBoidManager;

protected:

};
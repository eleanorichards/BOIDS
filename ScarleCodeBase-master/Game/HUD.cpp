#include "HUD.h"
#include "TextGO2D.h"
#include <sstream>


HUD::HUD()
{
}

HUD::~HUD()
{
}

//void HUD::Draw(DrawData * _DD)
//{
//	char boidChar = pBoidManager->getBoidsInScene();
//	std::string numOfBoids = (getNumOfBoidsAsString());
//	m_Sprites->Begin();
//	m_Font->DrawString(m_Sprites.get(), boidChar, XMFLOAT2(500, 20),
//		Colors::ForestGreen);
//	/*numOfBoids.SetPos(Vector2(100, 0));
//	numOfBoids.SetColour(Color((float*)&DirectX::Colors::Yellow));
//	numOfBoids.Draw(_DD);*/
//	
//}



//std::string HUD::getNumOfBoidsAsString()
//{
//	char boidChar = pBoidManager->getBoidsInScene();
//	std::stringstream bString;
//	bString << pBoidManager->getBoidsInScene();
//	return bString.str();
//}

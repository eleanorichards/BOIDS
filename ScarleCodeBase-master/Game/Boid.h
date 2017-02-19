#pragma once
#include "CMOGO.h"

class Boid : public CMOGO
{
public:
	Boid(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF);
	~Boid();

	void Spawn(Vector3 _pos, Vector3 _scale, Vector3 _dir);
	virtual void Tick(GameData* _GD) override;
	virtual void Draw(DrawData* _DD) override;
	void SetAlive(bool isAlive);

	bool isAlive() { return m_alive; }
private:
	Vector3 m_target; // I am travelling towards this location
	Vector3 m_dir;
	Vector3 m_up;
	Vector3 travelDirection;
	int max = 100;
	int min = 50;
	bool m_alive;
};
#pragma once
#include "CMOGO.h"

class Boid : public CMOGO
{
public:
	Boid(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF);
	~Boid();

	void Spawn(Vector3 _pos, Vector3 _scale, Vector3 _dir);
	void SetAlive(bool isAlive);
	void setVelocity(Vector3 velocity);
	void setPosition(Vector3 position);
	void setRotation(float yaw, float pitch);
	virtual void Tick(GameData* _GD) override;
	virtual void Draw(DrawData* _DD) override;

	Vector3 getVelocity() { return m_vel; }
	Vector3 GetPos() { return m_pos; }
	
	bool isAlive() { return m_alive; }


private:
	Vector3 m_target; // I am travelling towards this location
	Vector3 m_dir;
	Vector3 m_vel;
	Vector3 m_up;
	Vector3 travelDirection;
	Vector3 randomDirection;

	bool inBoundingBox = true;
	bool m_alive;
	int max = 100;
	int min = 50;
	float maxVelocity = 30;
	float minVelocity = -30;
};
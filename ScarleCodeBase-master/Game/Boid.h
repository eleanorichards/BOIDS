#pragma once
#include "VBGO.h"
#include "vertex.h"

class Boid : public VBGO
{
public:
	Boid(ID3D11Device* _pd3dDevice);
	~Boid();

	void Spawn(Vector3 _pos, Vector3 _scale, Vector3 _dir, GameData* _GD);
	void SetAlive(bool isAlive);
	void setVelocity(Vector3 velocity);
	void setPosition(Vector3 position);
	void setRotation(float yaw, float pitch);
	void setAcceleration(Vector3 _acceleration);

	virtual void Tick(GameData* _GD) override;
	virtual void Draw(DrawData* _DD) override;

	Vector3 getVelocity() { return m_vel; }
	Vector3 getAccleration() { return m_acc; }

	Vector3 GetPos() { return m_pos; }
	
	bool isAlive() { return m_alive; }


private:
	Vector3 m_target; // I am travelling towards this location
	Vector3 m_dir;
	Vector3 m_vel;
	Vector3 m_up;
	Vector3 m_acc;
	Vector3 travelDirection;
	Vector3 initialDirection;
	Vector3 acceleration;

	bool inBoundingBox = true;
	bool m_alive;
	int max = 100;
	int min = 50;
	//so they don't speed around everywhere
	float maxAcceleration = 0.7;
	float minAcceleration = -0.7;

	myVertex* m_vertices;

};
#include "CameraControl.h"
#include "GameData.h"


CameraControl::CameraControl()
{

}

CameraControl::~CameraControl()
{

}

void CameraControl::Tick(GameData * _GD)
{
	float rotSpeed = 2.0f * _GD->m_dt;
	if (_GD->m_keyboardState[DIK_A] & 0x80)
	{
		m_yaw += rotSpeed;
	}
	if (_GD->m_keyboardState[DIK_D] & 0x80)
	{
		m_yaw -= rotSpeed;
	}
	if (_GD->m_keyboardState[DIK_W] & 0x80)
	{
		m_pitch += rotSpeed;
	}
	if (_GD->m_keyboardState[DIK_S] & 0x80)
	{
		m_pitch -= rotSpeed;
	}
	GameObject::Tick(_GD);

}

void CameraControl::Draw(DrawData * _DD)
{
}

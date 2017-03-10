#include "TPSCamera.h"
#include "GameData.h"

TPSCamera::TPSCamera(float _fieldOfView, float _aspectRatio, float _nearPlaneDistance, float _farPlaneDistance, GameObject* _target, Vector3 _up, Vector3 _dpos)
	:Camera(_fieldOfView, _aspectRatio, _nearPlaneDistance, _farPlaneDistance, _up)
{
	m_targetObject = _target;
	m_dpos = _dpos;
}

TPSCamera::~TPSCamera()
{

}

void TPSCamera::Tick(GameData* _GD)
{
	//Set up position of camera and target position of camera based on new position and orientation of target object
	Matrix rotCam = Matrix::CreateFromYawPitchRoll(m_targetObject->GetYaw(), m_targetObject->GetPitch(), 0.0f);
	m_target = m_targetObject->GetPos();
	m_pos = m_target + Vector3::Transform(m_dpos, rotCam) ;
	/*float rotSpeed = 2.0f * _GD->m_dt;
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
	}*/
	//and then set up proj and view matrices
	Camera::Tick(_GD);
}


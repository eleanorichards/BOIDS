#ifndef _CAMERACONTROL_H_
#define _CAMERACONTROL_H_

#include "gameobject.h"


class CameraControl :  public GameObject
{
public:
	CameraControl();
	~CameraControl();

	virtual void Tick(GameData* _GD) override;
	virtual void Draw(DrawData* _DD) override;

private:

};

#endif

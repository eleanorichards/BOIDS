#include "GameObject2D.h"
#include "gamedata.h"
#include "DrawData2D.h"
#include "helper.h"

using namespace DirectX;

GameObject2D::GameObject2D()
{
	m_colour = Color(1.0f, 1.0f, 1.0f, 1.0f);
	m_pos = Vector2::Zero;
	m_rotation = 0.0f;
	m_scale = Vector2::One;
}

void GameObject2D::DrawScreenSpace(DrawData2D * _DD)
{
}

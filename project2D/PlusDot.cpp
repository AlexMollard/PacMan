#include "PlusDot.h"



PlusDot::PlusDot(const char* FileName, Grid* _Grid) : GameObject(FileName, _Grid)
{
	_Collider = new Collider(Vector2(-25, -25) / 4, Vector2(25, 25) / 4);
	_Texture = new aie::Texture("./textures/Dot.png");
	_DotTexture = new aie::Texture("./textures/Dot.png");
	SetName("PlusDot");
	_Eaten = false;
}

PlusDot::~PlusDot()
{
}

void PlusDot::OnCollision(GameObject * OtherObject)
{
	if (OtherObject->GetName() == "PacMan" && _Eaten == false)
	{
		_Eaten = true;
	}
}

void PlusDot::Update(float deltaTime)
{
	if (_Eaten)
	{
		_Texture = nullptr;
	}
}

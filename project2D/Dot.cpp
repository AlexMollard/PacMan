#include "Dot.h"
#include <iostream>
using namespace std;

Dot::Dot(const char* FileName, Grid* _Grid) : GameObject(FileName, _Grid)
{
	_Collider = new Collider(Vector2(-25, -25) / 4, Vector2(25, 25) / 4);
	_DotTexture = new aie::Texture("./textures/Dot.png");
	SetName("Dot");
	_Eaten = false;
}


Dot::~Dot()
{
}

void Dot::OnCollision(GameObject* OtherObject)
{
	if (OtherObject->GetName() == "PacMan" && _Eaten == false)
	{
		_Eaten = true;
	}
}

void Dot::Update(float deltaTime)
{
	if (_Eaten)
	{
		_Texture = nullptr;
	}
}

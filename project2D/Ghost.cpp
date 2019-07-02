#include "Ghost.h"

#include <iostream>
using namespace std;

Ghost::Ghost(const char* FileName, Grid* _Grid) : GameObject(FileName, _Grid)
{
	_Collider = new Collider(Vector2(-40, -40) / 2, Vector2(40, 40) / 2);
	this->_Grid = _Grid;
	SetName("Ghost");
}


Ghost::~Ghost()
{
}

void Ghost::Update(float deltaTime)
{
	if (_Velocity.magnitude() > 200)
	{
		_Velocity.normalise();
		_Velocity *= 200;
	}
	_Position = GetPosition();
	_Position = _Position + (_Velocity * deltaTime);


	SetPosition(_Position);
}

void Ghost::OnCollision(GameObject* OtherObject)
{

}
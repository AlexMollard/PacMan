#include "Wall.h"
#include <iostream>
using namespace std;

Wall::Wall(const char* FileName, Grid* _Grid) : GameObject(FileName, _Grid)
{
	_Collider = new Collider(Vector2(-25, -25) / 2, Vector2(25, 25) / 2);

	SetName("Wall");
}


Wall::~Wall()
{
}

void Wall::OnCollision(GameObject* OtherObject)
{
	
}
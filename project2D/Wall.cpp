#include "Wall.h"
#include <iostream>
using namespace std;

Wall::Wall(const char* FileName) : GameObject(FileName)
{
	_Collider = new Collider(Vector2(-50, -50), Vector2(50, 50));
	SetName("Wall");
}


Wall::~Wall()
{
}

void Wall::OnCollision(GameObject* OtherObject)
{
	
}
#include "Wall.h"



Wall::Wall(const char* FileName) : GameObject(FileName)
{
	_Collider = new Collider(Vector2(-20, -20), Vector2(20, 20));
	SetName("Wall");
}


Wall::~Wall()
{
}

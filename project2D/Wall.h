#pragma once
#include "GameObject.h"
#include "Renderer2D.h"
class Wall : public GameObject
{
public:
	Wall(const char* FileName, Grid* _Grid);
	~Wall();

	void OnCollision(GameObject* OtherObject);
};


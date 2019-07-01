#pragma once
#include "GameObject.h"
#include "Renderer2D.h"
class Wall : public GameObject
{
public:
	Wall(const char* FileName);
	~Wall();

	void OnCollision(GameObject* OtherObject);
};


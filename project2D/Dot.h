#pragma once
#include "GameObject.h"
#include "Renderer2D.h"
class Dot : public GameObject
{
public:
	Dot(const char* FileName, Grid* _Grid);
	~Dot();

	void OnCollision(GameObject* OtherObject);
	void Update(float deltaTime);
	aie::Texture* _DotTexture;
	bool _Eaten;
};
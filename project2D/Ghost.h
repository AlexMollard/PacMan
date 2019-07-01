#pragma once
#include "GameObject.h"
#include "Renderer2D.h"
class Ghost : public GameObject
{
public:
	Ghost(const char* FileName);
	~Ghost();

	void Update(float deltaTime);
	void OnCollision(GameObject* OtherObject);
protected:
	Vector2 _Velocity;
	Vector2 _Position;
	Vector2 ForwardBuf;
};


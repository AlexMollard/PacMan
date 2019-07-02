#pragma once
#include "GameObject.h"
#include "Renderer2D.h"

enum AIState
{
	_WANDER,
	_CHASE,
	_FLEE
};

class Ghost : public GameObject
{
public:
	Ghost(const char* FileName, Grid* _Grid);
	~Ghost();

	void Update(float deltaTime);
	void OnCollision(GameObject* OtherObject);

private:
	void Wander(float deltaTime);
	void Chase(float deltaTime);
	void Flee(float deltaTime);

protected:
	Vector2 _Velocity;
	Vector2 _Position;
	Vector2 ForwardBuf;
	Grid* _Grid;
};


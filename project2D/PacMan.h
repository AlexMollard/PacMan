#pragma once
#include "GameObject.h"
#include "Renderer2D.h"

class PacMan : public GameObject
{
public:
	PacMan(Grid* _Grid);
	~PacMan();

	void Update(float deltaTime);
	void OnCollision(GameObject* OtherObject);

	std::string GetName();

	aie::Texture* GetShipTexture();
	aie::Texture* GetShipHitTexture();
	void SetTexture(aie::Texture* tex);

	std::string _Name;
	float _Speed;
	int _Health;
	float _Timer;
	float time;
	float _Acceleration = 0.0f;
	Vector2 _Velocity;
	Vector2 _Position;
	Vector2 _PrevPosition;
	Vector2 ForwardBuf;
	Grid* _Grid;
	aie::Texture*	_PacmanClosedTexture;
	aie::Texture*	_PacmanOpenTexture;

	Vector2 _StartPos;
	Vector2 _EndPos;
};
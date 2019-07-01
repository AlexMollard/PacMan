#pragma once
#include "GameObject.h"
#include "Renderer2D.h"

class PacMan : public GameObject
{
public:
	PacMan();
	~PacMan();

	void Update(float deltaTime);
	void OnCollision(GameObject* OtherObject);
	void Hit();
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
	Vector2 ForwardBuf;


	aie::Texture*	_PacmanClosedTexture;
	aie::Texture*	_PacmanOpenTexture;
};
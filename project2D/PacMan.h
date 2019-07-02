#pragma once
#include "GameObject.h"
#include "Renderer2D.h"
#include "Node.h"
#include "Grid.h"

class PacMan : public GameObject
{
public:
	PacMan(Grid* _Grid);
	~PacMan();

	void Update(float deltaTime);
	void OnCollision(GameObject* OtherObject);
	void Draw(aie::Renderer2D* renderer);
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
	Vector2 _NextPosition;
	Vector2 _PrevPosition;
	Vector2 ForwardBuf;
	Vector2 _Direction;
	Node* _nextNode;
	Grid* _Grid;
	aie::Texture*	_PacmanClosedTexture;
	aie::Texture*	_PacmanOpenTexture;

	Vector2 _StartPos;
	Vector2 _EndPos;
	Node* _CurrentNode;
	int _PathCurrentNode;
	std::vector<Vector2> _Path;
};
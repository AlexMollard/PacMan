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
	void Draw(aie::Renderer2D* renderer);
	Vector2 RoundToNode(Vector2 _Pos);
	void GetPacManPos(GameObject* _PacMan);

private:
	void Wander(float deltaTime);
	void Chase(float deltaTime);
	void Flee(float deltaTime);

protected:
	Vector2 _Velocity;
	Vector2 _Position;
	Vector2 ForwardBuf;
	Grid* _Grid;
	Vector2 _Direction;
	Node* _nextNode;

	int _Timer;
	Vector2 _PacManPos;
	Vector2 _StartPos;
	Vector2 _EndPos;
	Node* _CurrentNode;
	int _PathCurrentNode;
	std::vector<Vector2> _Path;

	float _NodeSizeF;
	int _NodeSizeI;
};


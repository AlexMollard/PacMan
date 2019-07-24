#pragma once
#include "GameObject.h"
#include "Renderer2D.h"
#include "Node.h"

enum AIState
{
	_WANDER,
	_CHASE,
	_FLEE
};

class Ghost : public GameObject
{
public:
	Ghost(Grid* _Grid, int ghostnum);
	~Ghost();

	void Update(float deltaTime);
	void OnCollision(GameObject* OtherObject);
	void Draw(aie::Renderer2D* renderer);
	Vector2 RoundToNode(Vector2 _Pos);
	void GetPacManPos(GameObject* _PacMan);
	void GetPacManEndPos(Vector2 PacManEndPos);
	void PathTracing(float deltaTime);
	void SetSpawn(Vector2 Spawn) { _Spawn = Spawn; };
	Vector2 GetRandomNode();
	void Respawn();
private:
	void Coward(float deltaTime);
	void Chase(float deltaTime);
	void Ambush(float deltaTime);
	void WanderToCorner(float deltaTime);
	void Flee(float deltaTime);

	aie::Texture*	_GhostOrange;
	aie::Texture*	_GhostCyan;
	aie::Texture*	_GhostRed;
	aie::Texture*	_GhostPurple;

protected:
	Vector2 _Velocity;
	Vector2 _Position;
	Vector2 ForwardBuf;
	Grid* _Grid;
	Vector2 _Direction;
	Node* _nextNode;

	int _Timer;
	Vector2 _PacManPos;
	Vector2 _PacManEndPos;
	Vector2 _StartPos;
	Vector2 _EndPos;
	Vector2 _Spawn;
	Node* _CurrentNode;
	int _PathCurrentNode;
	std::vector<Vector2> _Path;

	float _NodeSizeF;
	int _NodeSizeI;

	bool _CowardRun;
};


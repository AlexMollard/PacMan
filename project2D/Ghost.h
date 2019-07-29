#pragma once
#include "GameObject.h"
#include "Renderer2D.h"
#include "Node.h"

enum AIState
{
	_AMBUSH,
	_CHASE,
	_RANDOM,
	_COWARD,
	_FLEE
};

class Ghost : public GameObject
{
public:
	Ghost(Grid* _Grid, int ghostnum);
	~Ghost();

	void ResetGhosts();
	void Respawn();
	void SetSpawn(Vector2 Spawn) { _Spawn = Spawn; };

	void Update(float deltaTime);
	void CheckState(float deltaTime);
	void Draw(aie::Renderer2D* renderer);

	Vector2 GetRandomNode();
	Vector2 RoundToNode(Vector2 _Pos);
	void PathTracing(float deltaTime);

	void GetPacManPos(GameObject* _PacMan);
	void GetPacManEndPos(Vector2 PacManEndPos);

	void OnCollision(GameObject* OtherObject);

	void SetFlee(bool flee) { _Flee = flee; };
	void SetTimer(float time) { _Timer = time; };
private:
	void Coward(float deltaTime);
	void Chase(float deltaTime);
	void Ambush(float deltaTime);
	void Random(float deltaTime);
	void Flee(float deltaTime);

	Grid* _Grid;

	Node* _nextNode;
	Node* _CurrentNode;

	std::vector<Vector2> _Path;

	int _State;
	int _Timer;
	int _PathCurrentNode;
	int _NodeSizeI;
	int _GhostNumber;

	float _NodeSizeF;
	
	bool _CowardRun;
	bool _Flee;

	Vector2 _Direction;
	Vector2 _Velocity;
	Vector2 _Position;
	Vector2 ForwardBuf;
	Vector2 _PacManPos;
	Vector2 _PacManEndPos;
	Vector2 _StartPos;
	Vector2 _EndPos;
	Vector2 _Spawn;

	aie::Texture*	_GhostOrange;
	aie::Texture*	_GhostCyan;
	aie::Texture*	_GhostRed;
	aie::Texture*	_GhostPurple;
	aie::Texture*	_Scared;
};


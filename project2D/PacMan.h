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
	void SetPath();
	void Animate();
	Vector2 RoundToNode(Vector2 _Pos, std::string _Dir);

	float _NodeSizeF;
	int _NodeSizeI;
	std::string _Name;
	float _Timer;
	Vector2 _Position;
	Vector2 _NextPosition;
	Vector2 _PrevPosition;
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
	bool _CanDirection[4];
};
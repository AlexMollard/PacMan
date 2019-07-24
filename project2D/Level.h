#pragma once
#include "GameObject.h"
#include "CollisionManager.h"
#include "PacMan.h"
#include "Wall.h"
#include "Map.h"
#include "Grid.h"
#include "Ghost.h"
#include "Dot.h"
#include "Font.h"

class Level : public GameObject
{
public:
	Level();
	~Level();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer);
	void AddScore(int newScore); 
	void GameOver();
private:
	int _Score;
	CollisionManager* _collisionManager;
	PacMan* _PacMan;
	Grid* _Grid;
	std::vector<Wall*> _Wall;
	std::vector<Dot*> _Dot;
	std::vector<Ghost*> _Ghost;

	Vector2 _StartPos;
	Vector2 _EndPos;
	std::vector<Vector2> _Path;
	aie::Font*			_Font;
	aie::Texture*		_PacManTexture;


	int _Lifes;
};


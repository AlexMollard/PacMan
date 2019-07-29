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
#include "PlusDot.h"

class Level : public GameObject
{
public:
	Level();
	~Level();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer);
	bool GetPowerUp(); 
	void SetPowerUp(bool power); 
	void GameOver();
private:
	int _Score;
	CollisionManager* _collisionManager;
	PacMan* _PacMan;
	Grid* _Grid;
	std::vector<Wall*> _Wall;
	std::vector<Dot*> _Dot;
	std::vector<PlusDot*> _PlusDot;
	std::vector<Ghost*> _Ghost;

	Vector2 _StartPos;
	Vector2 _EndPos;
	std::vector<Vector2> _Path;
	aie::Font*			_Font;
	aie::Texture*		_PacManTexture;

	bool _PowerUp;
	int _Lifes;
	float _Timer;
};


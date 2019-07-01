#pragma once
#include "GameObject.h"
#include "CollisionManager.h"
#include "PacMan.h"
#include "Wall.h"
#include "Map.h"
class Level : public GameObject
{
public:
	Level();
	~Level();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer);
private:
	CollisionManager* _collisionManager;
	PacMan* _PacMan;
	std::vector<Wall*> _Wall;
};


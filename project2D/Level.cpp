#include "Level.h"

Level::Level()
{
	SetName("Level");
	_collisionManager = new CollisionManager();

	 _PacMan = new PacMan();
	 _PacMan->SetParent(this);
	 _PacMan->SetPosition(Vector2(500,500));
	 _PacMan->UpDateGlobalTransform();
	 _collisionManager->AddObject(_PacMan);

	 for (int x = 0; x < 15; x++)
	 {
		 for (int y = 0; y < 15; y++)
		 {
			 if (map[y][x] == 1)
			 {
				 _Wall.push_back(new Wall("./textures/Wall.png"));
				 _Wall.back()->SetParent(this);
				 _Wall.back()->SetPosition(Vector2(100 + 40 * x, 100 + 40 * y));
				 _Wall.back()->UpDateGlobalTransform();
				 _collisionManager->AddObject(_Wall.back());
			 }
		 }
	 }


	// _Tank = new Tank();
	// _Tank->SetParent(this);
	// _Tank->SetPosition(Vector2(500,500));
	// _Tank->UpDateGlobalTransform();
	// _collisionManager->AddObject(_Tank);
}

Level::~Level()
{
	delete _collisionManager;
	_collisionManager = nullptr;
}

void Level::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
	_collisionManager->Update(deltaTime);
}

void Level::Draw(aie::Renderer2D* renderer)
{
	GameObject::Draw(renderer);
	_collisionManager->Draw(renderer);
}
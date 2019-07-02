#include "Level.h"

#define NodeSize 100

Level::Level()
{
	SetName("Level");
	_collisionManager = new CollisionManager();
	_Grid = new Grid(15, 15);


	 for (int x = 0; x < 15; x++)
	 {
		 for (int y = 0; y < 15; y++)
		 {
			 if (map[y][x] == 5)
			 {
				 _PacMan = new PacMan(_Grid);
				 _PacMan->SetParent(this);
				 _PacMan->SetPosition(Vector2(100 + NodeSize * x, 100 + NodeSize * y));
				 _PacMan->UpDateGlobalTransform();
				 _collisionManager->AddObject(_PacMan);
			 }
			 else if (map[y][x] == 1)
			 {
				 _Wall.push_back(new Wall("./textures/Wall.png", _Grid));
				 _Wall.back()->SetParent(this);
				 _Wall.back()->SetPosition(Vector2(100 + NodeSize * x, 100 + NodeSize * y));
				 _Wall.back()->UpDateGlobalTransform();
			 }
			 else if (map[y][x] == 2)
			 {
				 _Wall.push_back(new Wall("./textures/Open.png", _Grid));
				 _Wall.back()->SetParent(this);
				 _Wall.back()->SetPosition(Vector2(100 + NodeSize * x, 100 + NodeSize * y));
				 _Wall.back()->UpDateGlobalTransform();
			 }
			 else if (map[y][x] == 3)
			 {
				 _Ghost.push_back(new Ghost("./textures/GhostPurple.png", _Grid));
				 _Ghost.back()->SetParent(this);
				 _Ghost.back()->SetPosition(Vector2(100 + NodeSize * x, 100 + NodeSize * y));
				 _Ghost.back()->UpDateGlobalTransform();
				 _collisionManager->AddObject(_Ghost.back());
			 }
		 }
	 }
}

Level::~Level()
{
	delete _collisionManager;
	_collisionManager = nullptr;
}

void Level::Update(float deltaTime)
{
	_Ghost.front()->GetPacManPos(_PacMan);
	GameObject::Update(deltaTime);
	_collisionManager->Update(deltaTime);
	_Grid->update(deltaTime);

}

void Level::Draw(aie::Renderer2D* renderer)
{
	_Grid->Draw(renderer);
	GameObject::Draw(renderer);
	_collisionManager->Draw(renderer);
	_PacMan->Draw(renderer);
	_Ghost.front()->Draw(renderer);


	////Draw Path
	//renderer->setRenderColour(1.0f, 1.0f, 0.0f);
	//for (int i = 1; i < _Path.size(); i++)
	//{
	//	renderer->drawLine(_Path[i - 1].x, _Path[i - 1].y, _Path[i].x, _Path[i].y, 3);
	//}
	//
	////Start point
	//renderer->setRenderColour(0.0f, 1.0f, 0.0f);
	//renderer->drawCircle(_StartPos.x, _StartPos.y, 10);
	//
	////End point
	//renderer->setRenderColour(1.0f, 0.0f, 0.0f);
	//renderer->drawCircle(_EndPos.x, _EndPos.y, 10);
}
#include "Level.h"
#include <iostream>
#define NodeSize 50

Level::Level()
{
	SetName("Level");
	_collisionManager = new CollisionManager();
	_Grid = new Grid(15, 15);
	_PacManTexture = new aie::Texture("./textures/PacManOpen.png");
	_Font = new aie::Font("./font/consolas.ttf", 32);
	_Score = 0;
	_Timer = 20.0f;
	_Lifes = 3;
	_PowerUp = false;

	 for (int x = 0; x < 15; x++)
	 {
		 for (int y = 0; y < 15; y++)
		 {
			 if (map[y][x] == 5)
			 {
				 _PacMan = new PacMan(_Grid);
				 _PacMan->SetParent(this);
				 _PacMan->SetPosition(Vector2(100 + NodeSize * x, 100 + NodeSize * y));
				 _PacMan->SetSpawn(Vector2(100 + NodeSize * x, 100 + NodeSize * y));
				 _PacMan->UpDateGlobalTransform();
				 _collisionManager->AddObject(_PacMan);
			 }
			 else if (map[y][x] == 0)
			 {
				 _Dot.push_back(new Dot("./textures/Dot.png", _Grid));
				 _Dot.back()->SetParent(this);
				 _Dot.back()->SetPosition(Vector2(100 + NodeSize * x, 100 + NodeSize * y));
				 _Dot.back()->UpDateGlobalTransform();
				 _Dot.back()->SetScale(Vector2(0.5f, 0.5f));
				 _collisionManager->AddObject(_Dot.back());
			 }
			 else if (map[y][x] == 1)
			 {
				 //Choose wall texture


				//if (map[y + 1][x] == 1 && map[y - 1][x] == 1 && map[y][x + 1] == 1 && y < 14 && y > 0 && x < 14 && x > 0) // Up, Down, Right
				//	_Wall.push_back(new Wall("./textures/Walls/UpDownRight.png", _Grid));

				//else if (map[y + 1][x] == 1 && map[y - 1][x] == 1 && map[y][x - 1] == 1 && y < 14 && y > 0 && x < 14 && x > 0) // Up, Down, Left
				//	_Wall.push_back(new Wall("./textures/Walls/UpDownLeft.png", _Grid));

				//else if (map[y + 1][x] == 1 && map[y - 1][x] != 1 && map[y][x + 1] == 1 && y < 14 && y > 0 && x < 14 && x > 0) // Right, Up
				//	_Wall.push_back(new Wall("./textures/Walls/UpRight.png", _Grid));

				//else if (map[y + 1][x] == 1 && map[y - 1][x] != 1 && map[y][x - 1] == 1 && y < 14 && y > 0 && x < 14 && x > 0) // Left, Up
				//	_Wall.push_back(new Wall("./textures/Walls/UpLeft.png", _Grid));

				//else if (map[y+1][x] == 1 && map[y+1][x] != 1 && y < 14 && y > 0)	// Up
				//	_Wall.push_back(new Wall("./textures/Walls/Up.png", _Grid));

				//else if (map[y + 1][x] != 1 && map[y + 1][x] == 1 && y < 14 && y > 0)	// Down
				//	_Wall.push_back(new Wall("./textures/Walls/Down.png", _Grid));

				//else if (map[y][x - 1] == 1 && map[y][x + 1] != 1 && x < 14 && x > 0)	// Right
				//	_Wall.push_back(new Wall("./textures/Walls/Right.png", _Grid));

				//else if (map[y][x - 1] != 1 && map[y][x + 1] == 1 && x < 14 && x > 0)	// Left
				//	_Wall.push_back(new Wall("./textures/Walls/Left.png", _Grid));

				//else if (map[y][x+1] == 1 && map[y][x - 1] == 1 && x < 14 && x > 0)		// Right, Left
				//	_Wall.push_back(new Wall("./textures/Walls/RightLeft.png", _Grid));

				//else if (map[y + 1][x] == 1 && map[y - 1][x] == 1 && y < 14 && y > 0)	// Up, Down
				//	_Wall.push_back(new Wall("./textures/Walls/UpDown.png", _Grid));

				//else

					 _Wall.push_back(new Wall("./textures/Walls/Wall.png", _Grid));		// Normal












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
				 _Ghost.push_back(new Ghost(_Grid, _Ghost.size()));
				 _Ghost.back()->SetParent(this);
				 _Ghost.back()->SetPosition(Vector2(100 + NodeSize * x, 100 + NodeSize * y)); 
				 _Ghost.back()->SetSpawn(Vector2(100 + NodeSize * x, 100 + NodeSize * y));
				 _Ghost.back()->UpDateGlobalTransform();
				 _collisionManager->AddObject(_Ghost.back());
			 }
			 else if (map[y][x] == 4)
			 {
				 _PlusDot.push_back(new PlusDot("./textures/Dot.png", _Grid));
				 _PlusDot.back()->SetParent(this);
				 _PlusDot.back()->SetPosition(Vector2(100 + NodeSize * x, 100 + NodeSize * y));
				 _PlusDot.back()->UpDateGlobalTransform();
				 _collisionManager->AddObject(_PlusDot.back());
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
	_Timer += deltaTime;

	if (_Lifes > 0)
	{
		for (int i = 0; i < _Ghost.size(); i++)
		{
			_Ghost[i]->GetPacManPos(_PacMan);

			if (_PacMan->_Path.size() > 0)
				_Ghost[i]->GetPacManEndPos(_PacMan->_Path.back());
		}
		GameObject::Update(deltaTime);
		_collisionManager->Update(deltaTime);
		_Grid->update(deltaTime);

		_Score = _PacMan->GetScore();
		if (_Lifes != _PacMan->GetLifes())
		{
			for (int i = 0; i < _Ghost.size(); i++)
			{
				_Ghost[i]->Respawn();
			}

			_PacMan->Respawn();

			_Lifes = _PacMan->GetLifes();
		}
	}

	if (_PacMan->_PowerUp == true && _PowerUp == false)
	{
		_PowerUp = true;

		for (int i = 0; i < _Ghost.size(); i++)
		{
			_Ghost[i]->SetFlee(true);
			_Ghost[i]->SetTimer(0.0f);
		}
		_Timer = 0.0f;
	}

	if (_Timer > 10.0f)
	{
		_PowerUp = false;
		_PacMan->_PowerUp = false;
		for (int i = 0; i < _Ghost.size(); i++)
		{
			_Ghost[i]->SetFlee(false);
		}
	}

}

void Level::Draw(aie::Renderer2D* renderer)
{
	_Grid->Draw(renderer);
	GameObject::Draw(renderer);
	_PacMan->Draw(renderer);

	for (int i = 0; i < _Ghost.size(); i++)
	{
		_Ghost[i]->Draw(renderer);
	}
	//_collisionManager->Draw(renderer);

	// output the score
	char score[32];
	sprintf_s(score, 32, "Score: %i", _Score);
	renderer->drawText(_Font, score, 385, 785);

	switch (_Lifes)
	{
	case 3:
		renderer->drawSprite(_PacManTexture, 200.0f, 850.0f, 0.0f, 0.0f, 4.71239f);
	case 2:
		renderer->drawSprite(_PacManTexture, 150.0f, 850.0f, 0.0f, 0.0f, 4.71239f);
	case 1:
		renderer->drawSprite(_PacManTexture, 100.0f, 850.0f, 0.0f, 0.0f, 4.71239f);
	default:
		break;
	}

	if (_Lifes <= 0)
	{
		renderer->drawText(_Font, "YOU LOST YOU DUMB HEAD", 100.0f, 850.0f);
	}
}

bool Level::GetPowerUp()
{
	return _PowerUp;
}

void Level::SetPowerUp(bool power)
{
	_PowerUp = power;
}

void Level::GameOver()
{

}

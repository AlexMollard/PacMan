#include "Ghost.h"
#include <random>
#include <iostream>
#include <time.h>
using namespace std;

Ghost::Ghost(Grid* _Grid, int ghostnum)
{
	_Collider = new Collider(Vector2(-10, -10), Vector2(10, 10));
	_GhostPurple = new aie::Texture("./textures/GhostPurple.png");
	_GhostCyan = new aie::Texture("./textures/GhostCyan.png");
	_GhostOrange = new aie::Texture("./textures/GhostOrange.png");
	_GhostRed = new aie::Texture("./textures/GhostRed.png");
	_CowardRun = false;

	switch (ghostnum)
	{
	case 0:
		_Texture = _GhostPurple;
		SetName("Purple");

		break;
	case 1:
		_Texture = _GhostCyan;
		SetName("Cyan");

		break;
	case 2:
		_Texture = _GhostOrange;
		SetName("Orange");

		break;
	case 3:
		_Texture = _GhostRed;
		SetName("Red");

		break;
	default:
		break;
	}

	this->_Grid = _Grid;
	 _NodeSizeF = 50;
	 _NodeSizeI = 50;
	 _Timer = 0;
	 srand(time(NULL));
}


Ghost::~Ghost()
{
}

void Ghost::Update(float deltaTime)
{
	if (GetName() == "Purple")
	{
		Chase(deltaTime);
	}
	else if (GetName() == "Cyan")
	{
		WanderToCorner(deltaTime);
	}
	else if(GetName() == "Orange")
	{
		Coward(deltaTime);
	}
	else if(GetName() == "Red")
	{
		Ambush(deltaTime);
	}

	aie::Input* input = aie::Input::getInstance();
	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT))
		cout << "X: " << input->getMouseX() << ", Y: " << input->getMouseY() << endl;
}

void Ghost::OnCollision(GameObject* OtherObject)
{

}

Vector2 Ghost::RoundToNode(Vector2 _Pos)
{
	int a = roundf(_Pos.x / _NodeSizeF);
	_Pos.x = a * _NodeSizeI;
	int b = roundf(_Pos.y / _NodeSizeF);
	_Pos.y = b * _NodeSizeI;

	return _Pos;
}

void Ghost::GetPacManPos(GameObject* _PacMan)
{
	_PacManPos = _PacMan->GetPosition();
}

void Ghost::GetPacManEndPos(Vector2 PacManEndPos)
{
	_PacManEndPos = PacManEndPos;
}

void Ghost::PathTracing(float deltaTime)
{
	if (_Path.size() > 0 && _PathCurrentNode < _Path.size())
	{
		_Direction = _Path[_PathCurrentNode] - _Position;
		_Direction.normalise();

		_Position.x += _Direction.x * 100.0f * deltaTime;
		_Position.y += _Direction.y * 100.0f * deltaTime;

		SetPosition(_Position);

		float dist = (_Position - _Path[_PathCurrentNode]).magnitude();
		if (dist < 0.5f)
		{
			_PathCurrentNode++;
			_Position = RoundToNode(_Position);
			_StartPos = _Position;

			if (_Name == "Red" || (_Name == "Orange" ))
				_PathCurrentNode = 1;
		}
	}
}

Vector2 Ghost::GetRandomNode()
{
	Vector2 _BufferPos;
	do
	{
		_BufferPos = RoundToNode(Vector2(rand() % 700 + 100, rand() % 700 + 100));
	} while (_Grid->GetNodeByPos(_BufferPos)->_Blocked);

	return _BufferPos;
}

void Ghost::Respawn()
{
	_Position = RoundToNode(_Spawn);
	SetPosition(_Position);
	_StartPos = RoundToNode(_Spawn);
	_PathCurrentNode = 0;
	_Grid->FindPath(_StartPos, _EndPos, _Path);
}

void Ghost::Coward(float deltaTime) // Orange Ghost		Needs to make him chase pacman but once he gets within a radius runs away to where he started
{
	_Timer += 1;
	_Position = GetPosition();

	if (_Timer == 1)
	{
		_EndPos = RoundToNode(_PacManPos);
		_PathCurrentNode = 0;
		_CowardRun = false;
		_StartPos = RoundToNode(_Position);
		_Grid->FindPath(_StartPos, _EndPos, _Path);
	}

	if (!_CowardRun)
	{
		_EndPos = RoundToNode(_PacManPos);
		_Grid->FindPath(_StartPos, _EndPos, _Path);

		if (!_CowardRun && (_Position - _PacManPos).magnitude() < 50)
		{
			_CowardRun = true;
			_EndPos = GetRandomNode();
		}
	}
	else
	{
			_Grid->FindPath(_StartPos, _EndPos, _Path);

		if (_PathCurrentNode == _Path.size() - 1)
		{
			_CowardRun = false;
		}
	}
	PathTracing(deltaTime);
}

void Ghost::Chase(float deltaTime) // Purple Ghost
{
	_Timer += 1;
	_Position = GetPosition();

	if (_Timer == 1)
	{
		_EndPos = _PacManPos;
		_PathCurrentNode = 0;
		_StartPos = _Position;
	}
	else if (_Path.size() < 2)
	{
		_EndPos = RoundToNode(_PacManPos);
		_Grid->FindPath(_StartPos, _EndPos, _Path);
		_PathCurrentNode = 0;
	}
	else if (_PathCurrentNode == _Path.size())
	{
		_EndPos = RoundToNode(_PacManPos);
		_Grid->FindPath(_StartPos, _EndPos, _Path);
		_PathCurrentNode = 0;
	}

	PathTracing(deltaTime);
}

void Ghost::Ambush(float deltaTime) // Red Ghost (End Point is in front of pac man)	EndPoint should be pacmans endpoint
{
	_Timer += 1;
	_Position = GetPosition();

	if (_Timer == 1)
	{
		_EndPos = RoundToNode(_PacManEndPos);
		_PathCurrentNode = 0;
		_StartPos = _Position;
		_Grid->FindPath(_StartPos, _EndPos, _Path);
	}

	//If end node is close to pacman make endpoint pacman
	if (_EndPos == RoundToNode(_PacManPos))
	{
		_EndPos = RoundToNode(_PacManPos);
	}
	else if (_PathCurrentNode > _Path.size())
		_EndPos = RoundToNode(_PacManPos);
	else
		_EndPos = RoundToNode(_PacManEndPos);

	_Grid->FindPath(_StartPos, _EndPos, _Path);
	PathTracing(deltaTime);
}

void Ghost::WanderToCorner(float deltaTime) // Cyan Ghost (Wanders to each corner)
{
	_Timer += 1;
	_Position = GetPosition();

	if (_Timer == 1)
	{
		_EndPos = GetRandomNode();
		_PathCurrentNode = 0;
		_StartPos = _Position;
		_Grid->FindPath(_StartPos, _EndPos, _Path);
	}
	
	PathTracing(deltaTime);

	if (_PathCurrentNode == _Path.size())
	{
		_EndPos = GetRandomNode();
		_PathCurrentNode = 0;
		_StartPos = _Position;
		_Grid->FindPath(_StartPos, _EndPos, _Path);
	}
}

void Ghost::Draw(aie::Renderer2D* renderer)
{
	renderer->setRenderColour(1.0f, 1.0f, 1.0f);
	renderer->drawSpriteTransformed3x3(_Texture, _GlobalTransform);


	//Draw Path

	//if (GetName() == "Orange")
	//{
	//	renderer->setRenderColour(1.0f, 1.0f, 0.0f);
	//
	//
	//	for (int i = 1; i < _Path.size(); i++)
	//	{
	//		renderer->drawLine(_Path[i - 1].x, _Path[i - 1].y, _Path[i].x, _Path[i].y, 3);
	//	}
	//
	//	//Start point
	//	renderer->setRenderColour(0.2f, 0.7f, 0.0f);
	//	renderer->drawCircle(_StartPos.x, _StartPos.y, 10);
	//
	//	//End point
	//	renderer->setRenderColour(0.7f, 0.0f, 0.2f);
	//	renderer->drawCircle(_EndPos.x, _EndPos.y, 10);
	//}
	renderer->setRenderColour(1.0f, 1.0f, 1.0f);
}
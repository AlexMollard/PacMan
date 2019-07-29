#include "Ghost.h"
#include <random>
#include <iostream>
#include <time.h>
using namespace std;

Ghost::Ghost(Grid* Grid, int ghostnum)
{
	_Collider = new Collider(Vector2(-10, -10), Vector2(10, 10));
	_GhostPurple = new aie::Texture("./textures/GhostPurple.png");
	_GhostCyan = new aie::Texture("./textures/GhostCyan.png");
	_GhostOrange = new aie::Texture("./textures/GhostOrange.png");
	_GhostRed = new aie::Texture("./textures/GhostRed.png");
	_Scared = new aie::Texture("./textures/ScaredGhost.PNG");
	_CowardRun = false;

	_GhostNumber = ghostnum;
	_Grid = Grid;
	_NodeSizeF = 50;
	_NodeSizeI = 50;
	_Timer = 0;
	srand(time(NULL));

	ResetGhosts();
}


Ghost::~Ghost()
{
}

void Ghost::ResetGhosts()
{
	switch (_GhostNumber)
	{
	case 0:
		_Texture = _GhostPurple;
		SetName("Purple");
		_State = _CHASE;
		break;
	case 1:
		_Texture = _GhostCyan;
		SetName("Cyan");
		_State = _RANDOM;
		break;
	case 2:
		_Texture = _GhostOrange;
		SetName("Orange");
		_State = _COWARD;
		break;
	case 3:
		_Texture = _GhostRed;
		SetName("Red");
		_State = _AMBUSH;
		break;
	default:
		break;
	}
}

void Ghost::Update(float deltaTime)
{
	CheckState(deltaTime);

	if (_Flee)
		_State = _FLEE;
	else
		ResetGhosts();

	//aie::Input* input = aie::Input::getInstance();
	//if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT))
	//	cout << "X: " << input->getMouseX() << ", Y: " << input->getMouseY() << endl;
}

void Ghost::CheckState(float deltaTime)
{
	switch (_State)
	{
	case _CHASE:
		Chase(deltaTime);
		break;
	case _RANDOM:
		Random(deltaTime);
		break;
	case _COWARD:
		Coward(deltaTime);
		break;
	case _AMBUSH:
		Ambush(deltaTime);
		break;
	case _FLEE:
		Flee(deltaTime);
		break;
	default:
		break;
	}
}

void Ghost::OnCollision(GameObject* OtherObject)
{
	if (_Flee && OtherObject->GetName() == "PacMan")
	{
		_Flee = false;
		Respawn();
		ResetGhosts();
		SetPosition(_Position);
	}
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

void Ghost::Coward(float deltaTime) // Get close to pacman then run
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

void Ghost::Chase(float deltaTime) // EndNode equals pacmans Position
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

void Ghost::Random(float deltaTime) // Cyan Ghost (Wanders to each corner)
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

void Ghost::Flee(float deltaTime)
{
	Random(deltaTime);
	_Texture = _Scared;
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
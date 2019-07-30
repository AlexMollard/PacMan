#include "PacMan.h"
#include "Input.h"
#include "Application.h"
#include <iostream>
#include <math.h>
#include "Dot.h"
using namespace std;

PacMan::PacMan(Grid* _Grid)
{
	_Collider = new Collider(Vector2(-20, -20), Vector2(20, 20));
	this->_Grid = _Grid;
	_PacmanClosedTexture = new aie::Texture("./textures/PacManClosed.png");
	_PacmanOpenTexture = new aie::Texture("./textures/PacManOpen.png");
	_Texture = _PacmanClosedTexture;
	_PathCurrentNode = 0;
	_nextNode = nullptr;
	_Name = "PacMan";
	SetName(_Name);
	_PowerUp = false;
	_Timer = 0;
	_NodeSizeF = 50.0f;
	_NodeSizeI = 50;
	_CanDirection[0] = true;
	_CanDirection[1] = true;
	_CanDirection[2] = true;
	_CanDirection[3] = true;
	_Score = 0;
	_Lifes = 3;
}

PacMan::~PacMan()
{
	_Texture = nullptr;
	
	if (_PacmanClosedTexture)
	{
		delete _PacmanClosedTexture;
		_PacmanClosedTexture = nullptr;
	}

	if (_PacmanOpenTexture)
	{
		delete _PacmanOpenTexture;
		_PacmanOpenTexture = nullptr;
	}

	if (_Collider)
	{
		delete _Collider;
		_Collider = nullptr;
	}
}

void PacMan::Update(float deltaTime)
{
	aie::Input* _Input = aie::Input::getInstance();

	_Position = GetPosition();
	_Timer += 10 * deltaTime;
	_PrevPosition = GetPosition();

	if (_Timer > 2)
	{
		Animate();
	}

	if (_Input->isKeyDown(aie::INPUT_KEY_A) || _Input->isKeyDown(aie::INPUT_KEY_S) || _Input->isKeyDown(aie::INPUT_KEY_D) || _Input->isKeyDown(aie::INPUT_KEY_W))
		SetPath();

	if (_Path.size() > 0 && _PathCurrentNode < _Path.size())
	{
		_Direction = _Path[_PathCurrentNode] - _Position;
		_Direction.normalise();
		_Position += _Direction * 100.0f * deltaTime;
		SetPosition(_Position);

		float dist = (_Position - _Path[_PathCurrentNode]).magnitude();
		if (dist < 3)
			_PathCurrentNode++;
	}
	else
	{
		_Position = RoundToNode(_Position, "None");
		SetPosition(_Position);
	}

	//Updates all objects
	GameObject::Update(deltaTime);
}

Vector2 PacMan::RoundToNode(Vector2 _Pos, std::string _Dir)
{
	if (_Dir == "RIGHT")
	{
		int a = roundf((_Pos.x + _NodeSizeF) / _NodeSizeF);
		_Pos.x = a * _NodeSizeI;
		int b = roundf(_Pos.y / _NodeSizeF);
		_Pos.y = b * _NodeSizeI;
	}
	else if (_Dir == "LEFT")
	{
		int a = roundf((_Pos.x - _NodeSizeF) / _NodeSizeF);
		_Pos.x = a * _NodeSizeI;
		int b = roundf(_Pos.y / _NodeSizeF);
		_Pos.y = b * _NodeSizeI;
	}
	else if (_Dir == "UP")
	{
		int a = roundf((_Pos.x) / _NodeSizeF);
		_Pos.x = a * _NodeSizeI;
		int b = roundf((_Pos.y + _NodeSizeF) / _NodeSizeF);
		_Pos.y = b * _NodeSizeI;
	}
	else if (_Dir == "DOWN")
	{
		int a = roundf((_Pos.x) / _NodeSizeF);
		_Pos.x = a * _NodeSizeI;
		int b = roundf((_Pos.y - _NodeSizeF) / _NodeSizeF);
		_Pos.y = b * _NodeSizeI;
	}
	else
	{
		int a = roundf(_Pos.x / _NodeSizeF);
		_Pos.x = a * _NodeSizeI;
		int b = roundf(_Pos.y / _NodeSizeF);
		_Pos.y = b * _NodeSizeI;
	}

	return _Pos;
}

void PacMan::Respawn()
{
	_Position = RoundToNode(_Spawn, "Spawn");
	SetPosition(_Position);
	_StartPos = _Position;
	_EndPos = _Position;
	_Grid->FindPath(_StartPos, _EndPos, _Path);
}

void PacMan::SetPath()
{
	aie::Input* _Input = aie::Input::getInstance();
	Vector2 _TempPosition = RoundToNode(_Position, "None");

	//Calculate Rotation
	float _Rotation = GetLocalRotation();
	if (_Input->isKeyDown(aie::INPUT_KEY_A) && _CanDirection[0])
	{
		Node* Test = _Grid->GetNodeByPos(_TempPosition + (Vector2(-50,0)));

		if (Test->_Blocked == false)
		{

			_Rotation = 1.5708;

			_Position = RoundToNode(_Position, "None");
			_StartPos = _Position;

			_NextPosition = RoundToNode(_Position, "LEFT");

			_nextNode = _Grid->GetNodeByPos(_NextPosition);

			while (_nextNode->GetBlocked() == false)
			{
				_NextPosition = RoundToNode(_NextPosition, "LEFT");

				Node* temp = _Grid->GetNodeByPos(_NextPosition);
				if (temp->GetBlocked())
					break;

				_nextNode = temp;
			}

			_CanDirection[0] = false;
			_CanDirection[1] = true;
			_CanDirection[2] = true;
			_CanDirection[3] = true;
			_PathCurrentNode = 1;
		}
	}
	else if (_Input->isKeyDown(aie::INPUT_KEY_D) && _CanDirection[1]) // RIGHT
	{
		Node* Test = _Grid->GetNodeByPos(_TempPosition + (Vector2(50, 0)));
		if (Test->_Blocked == false)
		{
			_Rotation = 4.71239;

			_Position = RoundToNode(_Position, "None");
			_StartPos = _Position;

			_NextPosition = RoundToNode(_Position, "RIGHT");

			_nextNode = _Grid->GetNodeByPos(_NextPosition);

			while (_nextNode->GetBlocked() == false)
			{
				_NextPosition = RoundToNode(_NextPosition, "RIGHT");

				Node* temp = _Grid->GetNodeByPos(_NextPosition);
				if (temp->GetBlocked())
					break;

				_nextNode = temp;
			}


			_CanDirection[0] = true;
			_CanDirection[1] = false;
			_CanDirection[2] = true;
			_CanDirection[3] = true;
			_PathCurrentNode = 1;
		}
	}
	else if (_Input->isKeyDown(aie::INPUT_KEY_W) && _CanDirection[2])
	{
		Node* Test = _Grid->GetNodeByPos(_TempPosition + (Vector2(0, 50)));

		if (Test->_Blocked == false)
		{
			_Rotation = 0;

			_Position = RoundToNode(_Position, "None");
			_StartPos = _Position;

			_NextPosition = RoundToNode(_Position, "UP");

			_nextNode = _Grid->GetNodeByPos(_NextPosition);

			while (_nextNode->GetBlocked() == false)
			{
				_NextPosition = RoundToNode(_NextPosition, "UP");

				Node* temp = _Grid->GetNodeByPos(_NextPosition);

				if (temp->GetBlocked())
					break;

				_nextNode = temp;
			}

			_CanDirection[0] = true;
			_CanDirection[1] = true;
			_CanDirection[2] = false;
			_CanDirection[3] = true;
			_PathCurrentNode = 1;
		}
	}
	else if (_Input->isKeyDown(aie::INPUT_KEY_S) && _CanDirection[3])
	{
		Node* Test = _Grid->GetNodeByPos(_TempPosition + (Vector2(0, -50)));

		if (Test->_Blocked == false)
		{
			_Rotation = 3.14159;

			_Position = RoundToNode(_Position, "None");
			_StartPos = _Position;

			_NextPosition = RoundToNode(_Position, "DOWN");

			_nextNode = _Grid->GetNodeByPos(_NextPosition);

			while (_nextNode->GetBlocked() == false)
			{
				_NextPosition = RoundToNode(_NextPosition, "DOWN");

				Node* temp = _Grid->GetNodeByPos(_NextPosition);
				if (temp->GetBlocked())
					break;

				_nextNode = temp;
			}

			_CanDirection[0] = true;
			_CanDirection[1] = true;
			_CanDirection[2] = true;
			_CanDirection[3] = false;
			_PathCurrentNode = 1;
		}
	}

	SetRotation(_Rotation);
	_EndPos = _nextNode->_Position;
	_Grid->FindPath(_StartPos, _EndPos, _Path);
}

void PacMan::Animate()
{
	if (_Texture == _PacmanClosedTexture)
		_Texture = _PacmanOpenTexture;
	else
		_Texture = _PacmanClosedTexture;

	_Timer = 0;
}

void PacMan::OnCollision(GameObject* OtherObject)
{
	if (OtherObject->GetName() == "Dot")
	{
		if (OtherObject->GetTexture() != nullptr)
		{	
			_Score += 10;
		}
	}

	if ((OtherObject->GetName() == "Red") || (OtherObject->GetName() == "Cyan") || (OtherObject->GetName() == "Orange") || (OtherObject->GetName() == "Purple"))
	{
		if (_PowerUp)
		{
			_Score += 100;
		}
		else
		{
			_Lifes -= 1;
			_CanDirection[0] = true;
			_CanDirection[1] = true;
			_CanDirection[2] = true;
			_CanDirection[3] = true;
			_PathCurrentNode = 0;
			_nextNode = nullptr;
		}
	}

	if (OtherObject->GetName() == "PlusDot")
	{
		if (OtherObject->GetTexture() != nullptr)
		{
			_PowerUp = true;
		}
	}
}

void PacMan::Draw(aie::Renderer2D * renderer)
{
	renderer->setRenderColour(1.0f, 1.0f, 0.0f);
	renderer->drawSpriteTransformed3x3(_Texture, _GlobalTransform);
	renderer->setRenderColour(1.0f, 1.0f, 1.0f);



	////Draw Path
	//renderer->setRenderColour(1.0f, 1.0f, 1.0f);
	//for (int i = 1; i < _Path.size(); i++)
	//{
	//	renderer->drawLine(_Path[i - 1].x, _Path[i - 1].y, _Path[i].x, _Path[i].y, 3);
	//}
	//
	////Start point
	//renderer->setRenderColour(0.2f, 0.7f, 0.0f);
	//renderer->drawCircle(_StartPos.x, _StartPos.y, 10);
	//
	////End point
	//renderer->setRenderColour(0.7f, 0.0f, 0.2f);
	//renderer->drawCircle(_EndPos.x, _EndPos.y, 10);
	
	renderer->setRenderColour(1.0f, 1.0f, 1.0f);
}
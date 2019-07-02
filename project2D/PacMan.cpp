#include "PacMan.h"
#include "Input.h"
#include "Application.h"
#include <iostream>
#include <math.h>
using namespace std;

PacMan::PacMan(Grid* _Grid)
{
	_Acceleration = 2000.0f;
	_Collider = new Collider(Vector2(-20, -20), Vector2(20, 20));
	this->_Grid = _Grid;
	_PacmanClosedTexture = new aie::Texture("./textures/PacManClosed.png");
	_PacmanOpenTexture = new aie::Texture("./textures/PacManOpen.png");
	_Texture = _PacmanClosedTexture;
	
	_PathCurrentNode = 0;
	_nextNode = nullptr;
	_Name = "PacMan";
	SetName(_Name);
	_Health = 100;
	_Timer = 0;
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
	//_Grid->update(deltaTime);
	time = deltaTime;
	_Timer += 10 * deltaTime;
	_PrevPosition = GetPosition();

	if (_Timer > 2)
	{
		if (_Texture == _PacmanClosedTexture)
			_Texture = _PacmanOpenTexture;
		else
			_Texture = _PacmanClosedTexture;

		_Timer = 0;
	}

	aie::Input* _Input = aie::Input::getInstance();

	//Vector2 _Forward(_TempPostion.x, _TempPostion.y);
	_Position = GetPosition();

	//Calculate Rotation
	float _Rotation = GetLocalRotation();
	if (_Input->wasKeyPressed(aie::INPUT_KEY_A))
	{
		Vector2 _TempPos;
		int Ta = roundf(_Position.x / 50.0f);
		_TempPos.x = Ta * 50;
		int Tb = roundf(_Position.y / 50.0f);
		_TempPos.y = Tb * 50;
		_StartPos = _TempPos;
		_Position = _TempPos;

		_Rotation = 1.5708;
		int a = roundf((_Position.x - 50.0f) / 50.0f);
		_NextPosition.x = a * 50;
		int b = roundf(_Position.y / 50.0f);
		_NextPosition.y = b * 50;

		_nextNode = _Grid->GetNodeByPos(_NextPosition);

		while (_nextNode->GetBlocked() == false)
		{
			int a = roundf((_NextPosition.x - 50.0f) / 50.0f);
			_NextPosition.x = a * 50;
			int b = roundf(_NextPosition.y / 50.0f);
			_NextPosition.y = b * 50;

			Node* temp = _Grid->GetNodeByPos(_NextPosition);
			if (temp->GetBlocked())
				break;

			_nextNode = temp;
		}
		_EndPos = _nextNode->_Position;

		if (_nextNode)
		{
			_Grid->FindPath(_StartPos, _EndPos, _Path);
		}
	}
	else if (_Input->wasKeyPressed(aie::INPUT_KEY_D)) // RIGHT
	{
		Vector2 _TempPos;
		int Ta = roundf(_Position.x / 50.0f);
		_TempPos.x = Ta * 50;
		int Tb = roundf(_Position.y / 50.0f);
		_TempPos.y = Tb * 50;
		_StartPos = _TempPos;
		_Position = _TempPos;

		_Rotation = 4.71239;
		int a = roundf((_Position.x + 50.0f) / 50.0f);
		_NextPosition.x = a * 50;
		int b = roundf(_Position.y / 50.0f);
		_NextPosition.y = b * 50;

		_nextNode = _Grid->GetNodeByPos(_NextPosition);

		while (_nextNode->GetBlocked() == false)
		{
			int a = roundf((_NextPosition.x + 50.0f) / 50.0f);
			_NextPosition.x = a * 50;
			int b = roundf(_NextPosition.y / 50.0f);
			_NextPosition.y = b * 50;

			Node* temp = _Grid->GetNodeByPos(_NextPosition);
			if (temp->GetBlocked())
				break;

			_nextNode = temp;
		}
		_EndPos = _nextNode->_Position;

		if (_nextNode)
		{
			_Grid->FindPath(_StartPos, _EndPos, _Path);
		}
	}
	else if (_Input->wasKeyPressed(aie::INPUT_KEY_W))
	{
		Vector2 _TempPos;
		int Ta = roundf(_Position.x / 50.0f);
		_TempPos.x = Ta * 50;
		int Tb = roundf(_Position.y / 50.0f);
		_TempPos.y = Tb * 50;
		_StartPos = _TempPos;
		_Position = _TempPos;

		_Rotation = 0;
		int a = roundf((_Position.x) / 50.0f);
		_NextPosition.x = a * 50;
		int b = roundf((_Position.y + 50.0f) / 50.0f);
		_NextPosition.y = b * 50;

		_nextNode = _Grid->GetNodeByPos(_NextPosition);

		while (_nextNode->GetBlocked() == false)
		{
			int a = roundf((_NextPosition.x) / 50.0f);
			_NextPosition.x = a * 50;
			int b = roundf((_NextPosition.y + 50.0f) / 50.0f);
			_NextPosition.y = b * 50;

			Node* temp = _Grid->GetNodeByPos(_NextPosition);

			if (temp->GetBlocked())
				break;

			_nextNode = temp;
		}
		_EndPos = _nextNode->_Position;

		if (_nextNode)
		{
			_Grid->FindPath(_StartPos, _EndPos, _Path);
		}
	}
	else if (_Input->wasKeyPressed(aie::INPUT_KEY_S))
	{
		Vector2 _TempPos;
		int Ta = roundf(_Position.x / 50.0f);
		_TempPos.x = Ta * 50;
		int Tb = roundf(_Position.y  / 50.0f);
		_TempPos.y = Tb * 50;
		_StartPos = _TempPos;
		_Position = _TempPos;

		_Rotation = 3.14159;
		int a = roundf((_Position.x) / 50.0f);
		_NextPosition.x = a * 50;
		int b = roundf((_Position.y - 50.0f) / 50.0f);
		_NextPosition.y = b * 50;

		_nextNode = _Grid->GetNodeByPos(_NextPosition);

		while (_nextNode->GetBlocked() == false)
		{
			int a = roundf((_NextPosition.x) / 50.0f);
			_NextPosition.x = a * 50;
			int b = roundf((_NextPosition.y - 50.0f) / 50.0f);
			_NextPosition.y = b * 50;

			Node* temp = _Grid->GetNodeByPos(_NextPosition);
			if (temp->GetBlocked())
				break;

			_nextNode = temp;
		}
		_EndPos = _nextNode->_Position;

		if (_nextNode)
		{
			_Grid->FindPath(_StartPos, _EndPos, _Path);
		}
	}

	
	SetRotation(_Rotation);
	/*if (_nextNode)
	{
		

		_Grid->FindPath(_StartPos, _EndPos, _Path);

	}*/

	if (_Path.size() > 0 && _PathCurrentNode < _Path.size())
	{
		_Direction = _Path[_PathCurrentNode] - _Position;
		_Direction.normalise();
		_Position += _Direction * 100.0f * deltaTime;
		SetPosition(_Position);
		float dist = (_Position - _Path[_PathCurrentNode]).magnitude();
		if (dist < 3)
		{
			_PathCurrentNode++;
		}

	}
	else
	{

		
		int a = roundf((_Position.x) / 50.0f);
		_Position.x = a * 50;
		int b = roundf(_Position.y / 50.0f);
		_Position.y = b * 50;
		SetPosition(_Position);
	}
		if (_PathCurrentNode == _Path.size())
		{
			_PathCurrentNode = 0;
			_Path.clear();

		}

	//Debug stuff
	//cout << "-------- New Update --------" << endl;
	//cout << _StartPos.x << "	" << _StartPos.y << endl;
	//cout << _EndPos.x << "	" << _EndPos.y << endl;


	//currentNode in .h
	//if path.size > 0
		//_Path[currentNode]

		//direction = _Path[currentNode] - pos
		//direction.normalise()


	//Updates all objects
	GameObject::Update(deltaTime);
}

void PacMan::OnCollision(GameObject* OtherObject)
{
	//_Velocity = Vector2(0, 0);
	//
	//int a = roundf(_PrevPosition.x / 50.0f);
	//_PrevPosition.x = a * 50;
	//int b = roundf(_PrevPosition.y / 50.0f);
	//_PrevPosition.y = b * 50;
	//SetPosition(_PrevPosition);

}

void PacMan::Draw(aie::Renderer2D * renderer)
{
	renderer->setRenderColour(1.0f, 1.0f, 0.0f);
	renderer->drawSpriteTransformed3x3(_Texture, _GlobalTransform);
	renderer->setRenderColour(1.0f, 1.0f, 1.0f);
	//
	//
	//
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
	//
	//renderer->setRenderColour(1.0f, 1.0f, 1.0f);
}

std::string PacMan::GetName()
{
	return _Name;
}

void PacMan::SetTexture(aie::Texture* tex)
{
	_Texture = tex;
}

aie::Texture* PacMan::GetShipTexture()
{
	return _PacmanClosedTexture;
}

aie::Texture* PacMan::GetShipHitTexture()
{
	return _PacmanOpenTexture;
}
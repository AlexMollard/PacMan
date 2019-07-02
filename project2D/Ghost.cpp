#include "Ghost.h"

#include <iostream>
using namespace std;

Ghost::Ghost(const char* FileName, Grid* _Grid) : GameObject(FileName, _Grid)
{
	_Collider = new Collider(Vector2(-40, -40), Vector2(40, 40));
	this->_Grid = _Grid;
	SetName("Ghost");
	 _NodeSizeF = 50;
	 _NodeSizeI = 50;
	 _Timer = 0;
}


Ghost::~Ghost()
{
}

void Ghost::Update(float deltaTime)
{
	_Timer += 1;
	_Position = GetPosition();

	if (_Timer == 1)
	{
		_EndPos = _PacManPos;
		_StartPos = _Position;
		_PathCurrentNode = 0;
	}

	_EndPos = _PacManPos;
	_Grid->FindPath(_StartPos, _EndPos, _Path);

	if (_Path.size() > 0 && _PathCurrentNode < _Path.size())
	{
		_Direction = _Path[_PathCurrentNode] - _Position;
		_Direction.normalise();
		if (_Direction.x > _Direction.y)
		{
			_Position.x += _Direction.x * 100.0f * deltaTime;
		}
		else
		{
			_Position.y += _Direction.y * 100.0f * deltaTime;
		}
		SetPosition(_Position);

		float dist = (_Position - _Path[_PathCurrentNode]).magnitude();
		if (dist < 1)
			_PathCurrentNode++;
	}

	cout << _PathCurrentNode << endl;
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

void Ghost::Draw(aie::Renderer2D* renderer)
{
	renderer->setRenderColour(1.0f, 1.0f, 1.0f);
	renderer->drawSpriteTransformed3x3(_Texture, _GlobalTransform);


	//Draw Path
	renderer->setRenderColour(1.0f, 0.0f, 1.0f);
	for (int i = 1; i < _Path.size(); i++)
	{
		renderer->drawLine(_Path[i - 1].x, _Path[i - 1].y, _Path[i].x, _Path[i].y, 3);
	}

	//Start point
	renderer->setRenderColour(0.2f, 0.7f, 0.0f);
	renderer->drawCircle(_StartPos.x, _StartPos.y, 10);

	//End point
	renderer->setRenderColour(0.7f, 0.0f, 0.2f);
	renderer->drawCircle(_EndPos.x, _EndPos.y, 10);

	renderer->setRenderColour(1.0f, 1.0f, 1.0f);
}
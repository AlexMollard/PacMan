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

	//Calculate Movement
	Vector3 _TempPostion = _LocalTransform[1];
	//Vector2 _Forward(_TempPostion.x, _TempPostion.y);
	_Position = GetPosition();

	//Calculate Rotation
	float _Rotation = GetLocalRotation();
	if (_Input->wasKeyPressed(aie::INPUT_KEY_A))
	{
		_Rotation = 1.5708;
		//_Velocity = _Velocity + (_Forward * _Acceleration);
		_Velocity.x = -_Acceleration;
		_Velocity.y = 0;
		int a = roundf(_Position.y / 50.0f);
		_Position.y = a * 50;
	}
	else if (_Input->wasKeyPressed(aie::INPUT_KEY_D))
	{
		_Rotation = 4.71239;
		//_Velocity = _Velocity + (_Forward * _Acceleration);
		_Velocity.x = _Acceleration;
		_Velocity.y = 0;
		int a = roundf(_Position.y / 50.0f);
		_Position.y = a * 50;
	}
	else if (_Input->wasKeyPressed(aie::INPUT_KEY_W))
	{
		_Rotation = 0;
		//_Velocity = _Velocity + (_Forward * _Acceleration);
		_Velocity.x = 0;
		_Velocity.y = _Acceleration;
		int a = roundf(_Position.x / 50.0f);
		_Position.x = a * 50;
	}
	else if (_Input->wasKeyPressed(aie::INPUT_KEY_S))
	{
		_Rotation = 3.14159;
		_Velocity.x = 0;
		_Velocity.y = -_Acceleration;
		int a = roundf(_Position.x / 50.0f);
		_Position.x = a * 50;
	}
	SetRotation(_Rotation);
		
	_StartPos = GetPosition();

	if (_Velocity.magnitude() > 200)
	{
		_Velocity.normalise();
		_Velocity *= 200;
	}

	_Position = _Position + (_Velocity * deltaTime);


	//int a = roundf(_Position.x / 50.0f);
	//_Position.x = a * 50;
	//int b = roundf(_Position.y / 50.0f);
	//_Position.y = b * 50;
	SetPosition(_Position);



	//Updates all objects
	GameObject::Update(deltaTime);
}

void PacMan::OnCollision(GameObject* OtherObject)
{
	_Velocity = Vector2(0, 0);
	
	int a = roundf(_PrevPosition.x / 50.0f);
	_PrevPosition.x = a * 50;
	int b = roundf(_PrevPosition.y / 50.0f);
	_PrevPosition.y = b * 50;
	SetPosition(_PrevPosition);

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
#include "PacMan.h"
#include "Input.h"
#include "Application.h"
#include <iostream>
using namespace std;

PacMan::PacMan()
{
	_Acceleration = 2000.0f;
	_Collider = new Collider(Vector2(-20, -20), Vector2(20, 20));

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

	if (_Collider2)
	{
		delete _Collider2;
		_Collider2 = nullptr;
	}
}

void PacMan::Update(float deltaTime)
{
	time = deltaTime;
	_Timer += 10 * deltaTime;

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
	Vector2 _Forward(_TempPostion.x, _TempPostion.y);


	if (_Input->isKeyDown(aie::INPUT_KEY_SPACE))
	{
		_Velocity = _Velocity + (_Forward * _Acceleration);
	}
	else
	{
		_Velocity = Vector2(0,0);
	}

	if (_Velocity.magnitude() > 100)
	{
		_Velocity.normalise();
		_Velocity *= 100;
	}
	_Position = GetPosition();
	_Position = _Position + (_Velocity * deltaTime);

	//Calculate Rotation
	float _Rotation = GetLocalRotation();
	if (_Input->isKeyDown(aie::INPUT_KEY_A))
	{
		_Rotation = 1.5708;
	}
	else if (_Input->isKeyDown(aie::INPUT_KEY_S))
	{
		_Rotation = 3.14159;
	}
	else if (_Input->isKeyDown(aie::INPUT_KEY_D))
	{
		_Rotation = 4.71239;
	}
	else if (_Input->isKeyDown(aie::INPUT_KEY_W))
	{
		_Rotation = 0;
	}
	SetRotation(_Rotation);

	//Sets ships position
	SetPosition(_Position);



	//Updates all objects
	GameObject::Update(deltaTime);
}

void PacMan::OnCollision(GameObject* OtherObject)
{
	
}

std::string PacMan::GetName()
{
	return _Name;
}

void PacMan::Hit()
{
	_Position = GetPosition();
	_Velocity = Vector2(0, 0);
	_Position = _Position + (_Velocity * time);
	_Health -= 10;
	SetPosition(_Position);
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
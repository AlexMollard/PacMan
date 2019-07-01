#include "PacMan.h"
#include "Input.h"
#include "Application.h"
#include <iostream>
using namespace std;

PacMan::PacMan()
{
	_Acceleration = 2000.0f;
	_Collider = new Collider(Vector2(-35, -60), Vector2(35, -50)); //Down
	_Collider2 = new Collider(Vector2(-35, 60), Vector2(35, 50)); //Up
	_Collider3 = new Collider(Vector2(60, -35), Vector2(50, 35)); //Right
	_Collider4 = new Collider(Vector2(-60, 35), Vector2(-50, -35)); //Left

	_PacmanClosedTexture = new aie::Texture("./textures/PacManClosed.png");
	_PacmanOpenTexture = new aie::Texture("./textures/PacManOpen.png");
	_Texture = _PacmanClosedTexture;
	
	_Name = "PacMan";
	SetName(_Name);
	_Health = 100;
	_Timer = 0;
	_Dir[0] = true;
	_Dir[1] = true;
	_Dir[2] = true;
	_Dir[3] = true;
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

	if (_Collider3)
	{
		delete _Collider3;
		_Collider3= nullptr;
	}

	if (_Collider4)
	{
		delete _Collider4;
		_Collider4 = nullptr;
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


	//Calculate Rotation
	float _Rotation = GetLocalRotation();
	if (_Input->isKeyDown(aie::INPUT_KEY_A) && _Dir[3])
	{
		_Rotation = 1.5708;
		_Velocity = _Velocity + (_Forward * _Acceleration);
		_Dir[0] = true;
		_Dir[2] = true;
		_Dir[3] = true;
	}
	else if (_Input->isKeyDown(aie::INPUT_KEY_S) && _Dir[0])
	{
		_Rotation = 3.14159;
		_Velocity = _Velocity + (_Forward * _Acceleration);
		_Dir[1] = true;
		_Dir[2] = true;
		_Dir[3] = true;
	}
	else if (_Input->isKeyDown(aie::INPUT_KEY_D) && _Dir[2])
	{
		_Rotation = 4.71239;
		_Velocity = _Velocity + (_Forward * _Acceleration);
		_Dir[0] = true;
		_Dir[1] = true;
		_Dir[3] = true;
	}
	else if (_Input->isKeyDown(aie::INPUT_KEY_W) && _Dir[1])
	{
		_Rotation = 0;
		_Velocity = _Velocity + (_Forward * _Acceleration);
		_Dir[0] = true;
		_Dir[2] = true;
		_Dir[1] = true;
	}
	
	SetRotation(_Rotation);
		


	if (_Velocity.magnitude() > 200)
	{
		_Velocity.normalise();
		_Velocity *= 200;
	}
	_Position = GetPosition();
	_Position = _Position + (_Velocity * deltaTime);


	SetPosition(_Position);



	//Updates all objects
	GameObject::Update(deltaTime);
}

void PacMan::OnCollision(GameObject* OtherObject)
{
	cout << "Down" << endl;
	_Velocity = Vector2(0, 0);
	
	_Dir[0] = false;

	_Position = GetPosition();
	_Position = _Position + Vector2(0, 2);


	SetPosition(_Position);

}

void PacMan::OnCollision2(GameObject* OtherObject)
{
	cout << "Up" << endl;
	_Velocity = Vector2(0, 0);

	_Dir[1] = false;

	_Position = GetPosition();
	_Position = _Position + Vector2(0, -2);


	SetPosition(_Position);
}

void PacMan::OnCollision3(GameObject* OtherObject)
{
	cout << "RIGHT" << endl;
	_Velocity = Vector2(0, 0);
	
	_Dir[2] = false;

	_Position = GetPosition();
	_Position = _Position + Vector2(-2, 0);


	SetPosition(_Position);
}

void PacMan::OnCollision4(GameObject* OtherObject)
{
	cout << "LEFT" << endl;
	_Velocity = Vector2(0, 0);

	_Dir[3] = false;

	_Position = GetPosition();
	_Position = _Position + Vector2(2, 0);


	SetPosition(_Position);
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
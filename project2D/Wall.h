#pragma once
#include "GameObject.h"
#include "Renderer2D.h"
class Wall : public GameObject
{
public:
	Wall(const char* FileName, Grid* _Grid);
	~Wall();

	void OnCollision(GameObject* OtherObject);

	//aie::Texture*	_WallUp;
	//aie::Texture*	_WallDown;
	//aie::Texture*	_WallUpDown;
	//
	//aie::Texture*	_WallRight;
	//aie::Texture*	_WallLeft;
	//aie::Texture*	_WallRightLeft;
	//
	//aie::Texture*	_WallRightUp;
	//aie::Texture*	_WallLeftUp;
	//aie::Texture*	_WallRightLeftUp;
	//
	//aie::Texture*	_WallRightDown;
	//aie::Texture*	_WallLeftDown;
	//aie::Texture*	_WallRightLeftDown;
	//
	//aie::Texture*	_WallUpDownRight;
	//aie::Texture*	_WallUpDownLeft;

};


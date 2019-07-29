#pragma once
#include "Dot.h"
class PlusDot : public GameObject
{
public:
	PlusDot(const char* FileName, Grid* _Grid);;
	~PlusDot();

	void OnCollision(GameObject* OtherObject);
	void Update(float deltaTime);
	
	void SetEaten(bool eat) { _Eaten = eat; };
	bool SetEaten() { return _Eaten; };

private:
	aie::Texture* _DotTexture;
	bool _Eaten;
};


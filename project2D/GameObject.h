#pragma once
#include "Matrix3.h"
#include "Vector2.h"
#include "Renderer2D.h"
#include "Texture.h"
#include "Collider.h"
#include <string.h>
#include <vector>

class GameObject
{
public:
	GameObject();
	GameObject(const char* TextureName);
	virtual ~GameObject();

	void UpDateGlobalTransform();

	virtual void Update(float deltaTime);
	virtual void Draw(aie::Renderer2D* renderer);

	virtual void OnCollision(GameObject* OtherObject);
	virtual void OnCollision2(GameObject* OtherObject);
	virtual void OnCollision3(GameObject* OtherObject);
	virtual void OnCollision4(GameObject* OtherObject);

	void SetPosition(Vector2 v2Pos);
	Vector2 GetPosition();

	void SetRotation(float radians);
	float GetRotation();
	float GetLocalRotation();
	bool collided;

	void SetScale(Vector2 v2Scale);
	Vector2 GetScale();

	void SetParent(GameObject* Parent);
	GameObject* GetParent();

	Vector2 _V2ColliderMin;
	Vector2 _V2ColliderMax;

	void SetLocalRotation(float newRotation);

	float GetScore();
	void SetScore(float newScore);

	std::string GameObject::GetName();
	void SetName(std::string name);
	std::string _Name;
	float _Score;



	Collider* GetCollider() { return _Collider; }
	Collider* GetCollider2() { return _Collider2; }
	Collider* GetCollider3() { return _Collider3; }
	Collider* GetCollider4() { return _Collider4; }
	void SetCollided(bool hit);
	bool GetCollided();
	bool HasCollider2();
	bool HasCollider3();
	bool HasCollider4();
protected:

	GameObject* _Parent;
	std::vector<GameObject*> _ChildList;

	Matrix3 _LocalTransform;
	Matrix3 _GlobalTransform;
	aie::Texture* _Texture;

	Collider* _Collider;
	Collider* _Collider2 = nullptr;
	Collider* _Collider3 = nullptr;
	Collider* _Collider4 = nullptr;
private:
	void AddChild(GameObject* Child);
	void RemoveChild(GameObject* Child);
};
#include "CollisionManager.h"
#include <iostream>


CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::Update(float deltaTime)
{
	for (int i = 0; i < _ObjectList.size(); i++)
	{
		GameObject* _Object = _ObjectList[i];
		if (_Object->GetName() == "Wall")
			continue;

		Collider* _FirstCollider = _Object->GetCollider();

		for (int j = 0; j < _ObjectList.size(); j++)
		{
			GameObject* _OtherObject = _ObjectList[j];
			Collider* _OtherCollider = _OtherObject->GetCollider();
		
			if (!_OtherCollider)
				continue;

			if (i == j)
				continue;

			Vector2 _Min = _FirstCollider->GetMin();
			Vector2 _Max = _FirstCollider->GetMax();
			Vector2 _OtherMin = _OtherCollider->GetMin();
			Vector2 _OtherMax = _OtherCollider->GetMax();


			if (_Max.x > _OtherMin.x &&_Max.y > _OtherMin.y &&
				_Min.x < _OtherMax.x &&_Min.y < _OtherMax.y)
			{
				_Object->OnCollision(_OtherObject);
			}
		}
	}
}

void CollisionManager::Draw(aie::Renderer2D* renderer)
{
	for (int i = 0; i < _ObjectList.size(); i++)
	{
		//if (_ObjectList[i]->GetName() == "Wall")
		//	continue;

		Collider* _collider = _ObjectList[i]->GetCollider();
		Vector2 v2Min = _collider->GetMin();
		Vector2 v2Max = _collider->GetMax();
	
		renderer->drawLine(v2Min.x, v2Min.y, v2Min.x, v2Max.y);
		renderer->drawLine(v2Min.x, v2Max.y, v2Max.x, v2Max.y);
		renderer->drawLine(v2Max.x, v2Max.y, v2Max.x, v2Min.y);
		renderer->drawLine(v2Max.x, v2Min.y, v2Min.x, v2Min.y);
	}
}

void CollisionManager::AddObject(GameObject* object)
{
	_ObjectList.push_back(object);
}

void CollisionManager::RemoveObject()
{
	_ObjectList.pop_back();
}

GameObject* CollisionManager::GetObject()
{
	return _ObjectList.back();
}
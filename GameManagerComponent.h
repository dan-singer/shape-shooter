#pragma once
#include "Component.h"
#include "UITextComponent.h"
#include "UITransform.h"
#include <DirectXMath.h>

class GameManagerComponent : public Component
{
public:
	//template for what could become a more in depth class depending on future functionallity
	//As of right now, it's just a container 
	void AddScore(int _score);
	int* GetScore();

	//Required methods
	virtual void Start() override;
	GameManagerComponent(Entity* entity) : Component(entity) { }

	virtual void Tick(float deltaTime) override;

private:

	int* m_score = 0;
	UITextComponent* textElement = nullptr;
	UITransform* textTransform = nullptr;
	void UpdateUI();

};


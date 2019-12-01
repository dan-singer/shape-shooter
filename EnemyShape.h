#pragma once
#include "Component.h"
class UITextComponent;

class EnemyShape : public Component
{
private:
	float m_trackSpeed = 1.0f;
	UITextComponent* m_scoreText = nullptr;
public:
	EnemyShape(Entity* entity) : Component(entity) { }

	virtual void Start() override;

	virtual void Tick(float deltaTime) override;

	virtual void OnCollisionBegin(Entity* other) override;
};


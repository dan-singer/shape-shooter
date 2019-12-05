#pragma once
#include "Component.h"
#include <functional>

typedef std::function<void()> Action;

class UITextComponent;

class EnemyShape : public Component
{
private:
	float m_trackSpeed = 1.0f;
	UITextComponent* m_scoreText = nullptr;
	UITextComponent* m_gameOverText = nullptr;
public:
	EnemyShape(Entity* entity) : Component(entity) { }

	virtual void Start() override;

	virtual void Tick(float deltaTime) override;

	virtual void OnCollisionBegin(Entity* other) override;



	Action OnLose = nullptr;
};


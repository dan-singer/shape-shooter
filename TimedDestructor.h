#pragma once
#include "Component.h"
class TimedDestructor : public Component
{
private:
	float m_duration = 2.0f;
	float m_timer = 0.0f;
public:

	TimedDestructor(Entity* entity) : Component(entity) { }

	// --------------------------------------------------------
	// Sets how long it will take for this component to destroy
	// its owner
	// @param float duration
	// @returns float
	// --------------------------------------------------------
	void SetDuration(float duration) { m_duration = duration; }


	virtual void Start() override;
	virtual void Tick(float deltaTime) override;

};


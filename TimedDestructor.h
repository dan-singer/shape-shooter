#pragma once
#include "Component.h"

// --------------------------------------------------------
// Component which destroys it's owner entity after the 
// duration has passed
// --------------------------------------------------------
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
	// --------------------------------------------------------
	void SetDuration(float duration) { m_duration = duration; }


	virtual void Start() override;
	virtual void Tick(float deltaTime) override;

};


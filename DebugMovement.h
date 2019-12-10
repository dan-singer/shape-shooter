#pragma once
#include "Component.h"
#include <DirectXMath.h>

class DebugMovement : public Component
{
private:
	DirectX::XMFLOAT2 prevMousePos = DirectX::XMFLOAT2(0, 0);
	float m_pitch = 0.0f;
	float m_yaw = 0.0f;
public:
	DebugMovement(Entity* entity) : Component(entity) { }

	virtual void Start() override;

	virtual void Tick(float deltaTime) override;


	virtual void OnMouseMove(WPARAM buttonState, int x, int y) override;

};


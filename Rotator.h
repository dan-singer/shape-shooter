#pragma once
#include "Component.h"
#include <DirectXMath.h>
class Rotator : public Component
{
public:
	DirectX::XMFLOAT3 eulerDelta = DirectX::XMFLOAT3(0, 0, 0);

	Rotator(Entity* entity) : Component(entity) { }

	virtual void Start() override;


	virtual void Tick(float deltaTime) override;

};


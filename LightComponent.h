#pragma once
#include "Component.h"
#include <DirectXMath.h>

// --------------------------------------------------------
// General light component that can be attached to an entity
// Position and direction are auto-acquired from the Transform
// --------------------------------------------------------
class LightComponent : public Component
{

public:
	enum Type
	{
		Directional = 0,
		Point,
		Spot
	};

	// --------------------------------------------------------
	// Light Struct that gets passed to the GPU
	// --------------------------------------------------------
	struct {
		Type type;
		DirectX::XMFLOAT3 direction; // 16 Bytes
		float range;
		DirectX::XMFLOAT3 position; // 32 Bytes
		float intensity; 
		DirectX::XMFLOAT3 color; // 48 Bytes
		float spotFalloff;
		DirectX::XMFLOAT3 padding; //64 bytes
	} m_data;



	virtual void Start() override;


	virtual void Tick(float deltaTime) override;

};


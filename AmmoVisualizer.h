#pragma once
#include <DirectXMath.h>
#include "Component.h"
class Launcher;
class MeshComponent;
class MaterialComponent;
// --------------------------------------------------------
// Component which reads and positions ammo visualization
// meshes relative to the parent's transform
// --------------------------------------------------------
class AmmoVisualizer : public Component
{
private:
	Entity* m_parent = nullptr;
	Launcher* m_parentLauncher = nullptr;
	MeshComponent* m_meshComponent = nullptr;
	MaterialComponent* m_materialComponent = nullptr;
	DirectX::XMFLOAT3 m_localOffset = DirectX::XMFLOAT3(-2.2f, -1.0f, 4);

public:

	void SetParent(Entity* parent) { m_parent = parent; }

	AmmoVisualizer(Entity* entity) : Component(entity) { }

	virtual void Start() override;

	virtual void Tick(float deltaTime) override;

};


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
	Entity* m_parent;
	Launcher* m_parentLauncher;
	MeshComponent* m_meshComponent;
	MaterialComponent* m_materialComponent;
	//DirectX::XMFLOAT3 m_localOffset = DirectX::XMFLOAT3(-2.2f, -1.5f, 5);
	DirectX::XMFLOAT3 m_localOffset = DirectX::XMFLOAT3(0, 0, 1);

public:

	void SetParent(Entity* parent) { m_parent = parent; }

	AmmoVisualizer(Entity* entity) : Component(entity) { }

	virtual void Start() override;

	virtual void Tick(float deltaTime) override;

};


#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Material.h"
#include <vector>
// --------------------------------------------------------
// Component which listens for inputs and spawns an Entity 
// on left mouse button down.
// --------------------------------------------------------
class Launcher : public Component
{
private:
	Material* m_ammoMaterial = nullptr;
	std::vector<Mesh*> m_ammoMeshes;
	int m_spawnIndex = 0;
	int m_totalSpawnedProjectiles = 0;
	float m_impulseMagnitude = 100.0f;

	bool m_wasPrevPressed = false;
	bool m_wasNextPressed = false;

	void WrapSpawnIndex();
	void SpawnProjectile();
public:
	Launcher(Entity* entity) : Component(entity) { }

	void SetAmmoMaterial(Material* material) { m_ammoMaterial = material; }
	void AddAmmoMesh(Mesh* newMesh) { m_ammoMeshes.push_back(newMesh); }
	void SetImpulseMagnitude(float magnitude) { m_impulseMagnitude = magnitude; }

	virtual void Start() override;
	virtual void Tick(float deltaTime) override;

	virtual void OnMouseDown(WPARAM buttonState, int x, int y) override;
	virtual void OnMouseWheel(float wheelDelta, int x, int y) override;

};


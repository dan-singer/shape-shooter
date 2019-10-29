#include "Launcher.h"
#include "World.h"
#include "MeshComponent.h"
#include "Entity.h"

void Launcher::SpawnProjectile()
{
	Entity* projectile = World::GetInstance()->Instantiate("projectile" + std::to_string(m_totalSpawnedProjectiles));
	//projectile->AddComponent<MeshComponent>()->m_mesh = m_ammoMeshes[m_spawnIndex];
	//projectile->AddComponent<MaterialComponent>()->m_material = m_ammoMaterial;
	//projectile->AddComponent<RigidBodyComponent>()->SetSphereCollider(1.0f);
	//projectile->StartAllComponents();
}

void Launcher::Start()
{
}

void Launcher::Tick(float deltaTime)
{
}

void Launcher::OnMouseDown(WPARAM buttonState, int x, int y)
{
	if (m_ammoCount > 0) {
		SpawnProjectile();
		--m_ammoCount;
		++m_totalSpawnedProjectiles;
	}
}

void Launcher::OnMouseWheel(float wheelDelta, int x, int y)
{
}

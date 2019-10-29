#include "Launcher.h"
#include "World.h"
#include "MeshComponent.h"
#include "Entity.h"
#include <bullet/LinearMath/btVector3.h>

using namespace DirectX;

void Launcher::SpawnProjectile()
{
	Transform* transform = GetOwner()->GetTransform();

	Entity* projectile = World::GetInstance()->Instantiate("projectile" + std::to_string(m_totalSpawnedProjectiles));
	projectile->AddComponent<MeshComponent>()->m_mesh = m_ammoMeshes[m_spawnIndex];
	projectile->AddComponent<MaterialComponent>()->m_material = m_ammoMaterial;
	RigidBodyComponent* rb = projectile->AddComponent<RigidBodyComponent>();
	rb->SetSphereCollider(1.0f);
	rb->m_mass = 1.0f;
	projectile->GetTransform()->SetPosition(transform->GetPosition());
	projectile->GetTransform()->SetRotation(transform->GetRotation());
	projectile->StartAllComponents();

	// TODO refactor RigidBodyComponent to accept XMFLOAT instead of btVector
	btVector3 impulse;
	XMFLOAT3 fwd = transform->GetForward();
	impulse.setX(fwd.x);
	impulse.setY(fwd.y);
	impulse.setZ(fwd.z);

	projectile->GetRigidBody()->ApplyImpulse(impulse * m_impulseMagnitude);
}

void Launcher::Start()
{
}

void Launcher::Tick(float deltaTime)
{
}

void Launcher::OnMouseDown(WPARAM buttonState, int x, int y)
{
	SpawnProjectile();
	++m_totalSpawnedProjectiles;
}

void Launcher::OnMouseWheel(float wheelDelta, int x, int y)
{
}

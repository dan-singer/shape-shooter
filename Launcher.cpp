#include "Launcher.h"
#include "World.h"
#include "MeshComponent.h"
#include "Entity.h"
#include <bullet/LinearMath/btVector3.h>
#include "TimedDestructor.h"

using namespace DirectX;

void Launcher::WrapSpawnIndex()
{
	// Avoid implicit casting
	int meshesSize = static_cast<int>(m_ammoMeshes.size());
	if (m_spawnIndex >= meshesSize) {
		m_spawnIndex = 0;
	}
	else if (m_spawnIndex < 0) {
		m_spawnIndex = m_ammoMeshes.size() - 1;
	}
}

void Launcher::SpawnProjectile()
{
	Transform* transform = GetOwner()->GetTransform();

	Entity* projectile = World::GetInstance()->Instantiate("projectile" + std::to_string(m_totalSpawnedProjectiles));
	projectile->AddComponent<MeshComponent>()->m_mesh = m_ammoMeshes[m_spawnIndex];
	projectile->AddComponent<MaterialComponent>()->m_material = m_ammoMaterial;
	RigidBodyComponent* rb = projectile->AddComponent<RigidBodyComponent>();
	rb->SetSphereCollider(1.0f);
	rb->m_mass = 1.0f; // Make sure the projectile has a non-zero mass, otherwise it will not move
	// Make the projectile be destroyed after 10 seconds
	projectile->AddComponent<TimedDestructor>()->SetDuration(10.0f);
	// Spawn in front of the player
	XMFLOAT3 spawnPos;
	XMFLOAT3 posData = transform->GetPosition();
	XMFLOAT3 fwdData = transform->GetForward();
	XMStoreFloat3(&spawnPos, XMVectorAdd(XMLoadFloat3(&posData), XMLoadFloat3(&fwdData) * 5)); 
	projectile->GetTransform()->SetPosition(spawnPos);
	projectile->GetTransform()->SetRotation(transform->GetRotation());
	// Add a tag to this entity so enemy shapes can detect it
	projectile->AddTag("player-shape");

	// Call start on this projectile so the rigidbody is ready before applying an impulse
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
	// TODO perhaps add an InputManager to simplify this
	if ((GetAsyncKeyState('Q') & 0x8000) && !m_wasPrevPressed) {
		--m_spawnIndex;
		WrapSpawnIndex();
	}
	if ((GetAsyncKeyState('E') & 0x8000) && !m_wasNextPressed) {
		++m_spawnIndex;
		WrapSpawnIndex();
	}

	m_wasPrevPressed = GetAsyncKeyState('Q') & 0x8000;
	m_wasNextPressed = GetAsyncKeyState('E') & 0x8000;
}

void Launcher::OnMouseDown(WPARAM buttonState, int x, int y)
{
	SpawnProjectile();
	++m_totalSpawnedProjectiles;
}

void Launcher::OnMouseWheel(float wheelDelta, int x, int y)
{
	if (wheelDelta > 0) {
		++m_spawnIndex;
	}
	else {
		--m_spawnIndex;

	}
	WrapSpawnIndex();
}

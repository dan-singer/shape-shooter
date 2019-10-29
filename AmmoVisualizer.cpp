#include "AmmoVisualizer.h"
#include "Transform.h"
#include "Entity.h"
#include "Component.h"
#include "Launcher.h"
#include "MeshComponent.h"
#include "MaterialComponent.h"

using namespace DirectX;

void AmmoVisualizer::Start()
{
	m_parentLauncher = m_parent->GetComponent<Launcher>();
	// TODO should Entity's GetMesh return the component or the actual mesh pointer we wouldn't have to do this?
	m_meshComponent = GetOwner()->GetComponent<MeshComponent>();
	m_materialComponent = GetOwner()->GetComponent<MaterialComponent>();
}

void AmmoVisualizer::Tick(float deltaTime)
{
	// Set the entity's position to always be in front of the camera
	XMFLOAT3 parentPosData = m_parent->GetTransform()->GetPosition();
	XMVECTOR parentPosition = XMLoadFloat3(&parentPosData);

	XMVECTOR localOffset = XMLoadFloat3(&m_localOffset);
	// Transform localOffset into global space
	XMFLOAT4 parentRotData = m_parent->GetTransform()->GetRotation();
	XMVECTOR parentRotation = XMLoadFloat4(&parentRotData);
	XMVECTOR globalOffset = XMVector3Rotate(localOffset, parentRotation);

	XMVECTOR newPosition = XMVectorAdd(parentPosition, globalOffset);
	XMFLOAT3 finalPos;
	XMStoreFloat3(&finalPos, newPosition);
	GetOwner()->GetTransform()->SetPosition(finalPos);


	GetOwner()->GetTransform()->SetRotation(m_parent->GetTransform()->GetRotation());

	// Make the mesh match what the launcher will launch
	m_meshComponent->m_mesh = m_parentLauncher->GetCurrentAmmoMesh();
	m_materialComponent->m_material = m_parentLauncher->GetAmmoMaterial();
}
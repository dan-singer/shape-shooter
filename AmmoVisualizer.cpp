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
	// Make the mesh match what the launcher will launch
	m_meshComponent->m_mesh = m_parentLauncher->GetCurrentAmmoMesh();
}
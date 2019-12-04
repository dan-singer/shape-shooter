#pragma
#include "ShapeSpawnerManager.h"
#include "Rotator.h"
#include "Entity.h"
#include "World.h"
#include "EnemyShape.h"
#include <DirectXMath.h>

using namespace DirectX;

ShapeSpawnerManagerComponent::ShapeSpawnerManagerComponent(Entity* entity) : Component(entity)
{
	srand(time(NULL));
	spawnTimer = 0.0f;
	timeUntilSpawn = 2.0f;
}

void ShapeSpawnerManagerComponent::Tick(float deltaTime)
{
	//update spawn timer
	spawnTimer += deltaTime;
	if (spawnTimer > timeUntilSpawn)
	{
		spawnShapes();//spawn shape
		spawnTimer = 0.0f;
		//pick a random number between 0 and 10
		int randomNum = rand() % 11;
		//create the next time a shape should spawn from now between 1.5 and 2.5 seconds
		timeUntilSpawn = 1.5f + (float)randomNum / 10.0f;
	}
}

void ShapeSpawnerManagerComponent::Start()
{
}

void ShapeSpawnerManagerComponent::spawnShapes()
{
	int type = rand() % 6;
	World* world = World::GetInstance();
	//XMVECTOR shipPos = world->m_mainCamera;
	//cubes
	if (type == 0)
	{
		Entity* cube1 = world->Instantiate("cube1");
		cube1->GetTransform()->SetPosition(XMFLOAT3(rand() % 10 - 5, rand() % 10 - 5, rand() % 10 - 5));
		cube1->AddComponent<MeshComponent>()->m_mesh = world->GetMesh("cube");
		cube1->AddComponent<MaterialComponent>()->m_material = world->GetMaterial("metal");
		cube1->AddComponent<RigidBodyComponent>()->SetBoxCollider(.5f, .5f, .5f);
		cube1->AddComponent<EnemyShape>();
		Rotator* rotCube = cube1->AddComponent<Rotator>();
		rotCube->eulerDelta.x = 1.0f;
		rotCube->eulerDelta.y = 1.0f;
	}
	//cones
	if (type == 1)
	{
		Entity* cone1 = world->Instantiate("cone1");
		cone1->GetTransform()->SetPosition(XMFLOAT3(rand() % 10 - 5, rand() % 10 - 5, rand() % 5));
		cone1->AddComponent<MeshComponent>()->m_mesh = world->GetMesh("cone");
		cone1->AddComponent<MaterialComponent>()->m_material = world->GetMaterial("metal");
		cone1->AddComponent<RigidBodyComponent>()->SetBoxCollider(.5f, .5f, .5f);
		cone1->AddComponent<EnemyShape>();

		Rotator* rotCone = cone1->AddComponent<Rotator>();
		rotCone->eulerDelta.x = 2.0f;
		rotCone->eulerDelta.y = 1.0f;
	}
	//cylinders
	if (type == 2)
	{
		Entity* cylinder1 = world->Instantiate("cylinder1");
		cylinder1->GetTransform()->SetPosition(XMFLOAT3(rand() % 10 - 5, rand() % 10 - 5, rand() % 5));
		cylinder1->AddComponent<MeshComponent>()->m_mesh = world->GetMesh("cylinder");
		cylinder1->AddComponent<MaterialComponent>()->m_material = world->GetMaterial("metal");
		cylinder1->AddComponent<RigidBodyComponent>()->SetBoxCollider(.5f, .5f, .5f);
		cylinder1->AddComponent<EnemyShape>();

		Rotator* rotCyl = cylinder1->AddComponent<Rotator>();
		rotCyl->eulerDelta.x = 5.0f;
		rotCyl->eulerDelta.y = 1.0f;
	}
	//helix
	if (type == 3)
	{
		Entity* helix1 = world->Instantiate("helix1");
		helix1->GetTransform()->SetPosition(XMFLOAT3(rand() % 10 - 5, rand() % 10 - 5, rand() % 5));
		helix1->AddComponent<MeshComponent>()->m_mesh = world->GetMesh("helix");
		helix1->AddComponent<MaterialComponent>()->m_material = world->GetMaterial("metal");
		helix1->AddComponent<RigidBodyComponent>()->SetBoxCollider(.5f, .5f, .5f);
		helix1->AddComponent<EnemyShape>();

		Rotator* rothelix = helix1->AddComponent<Rotator>();
		rothelix->eulerDelta.x = 1.0f;
		rothelix->eulerDelta.y = 5.0f;
	}
	//sphere
	if (type == 4)
	{
		Entity* sphere1 = world->Instantiate("sphere1");
		sphere1->GetTransform()->SetPosition(XMFLOAT3(rand() % 10 - 5, rand() % 10 - 5, rand() % 5));
		sphere1->AddComponent<MeshComponent>()->m_mesh = world->GetMesh("sphere");
		sphere1->AddComponent<MaterialComponent>()->m_material = world->GetMaterial("metal");
		sphere1->AddComponent<RigidBodyComponent>()->SetBoxCollider(.5f, .5f, .5f);
		sphere1->AddComponent<EnemyShape>();

		Rotator* rotSphere = sphere1->AddComponent<Rotator>();
		rotSphere->eulerDelta.x = 1.0f;
		rotSphere->eulerDelta.y = 1.0f;
	}
	//torus
	if (type == 5)
	{
		Entity* torus1 = world->Instantiate("torus1");
		torus1->GetTransform()->SetPosition(XMFLOAT3(rand() % 10 - 5, rand() % 10 - 5, rand() % 5));
		torus1->AddComponent<MeshComponent>()->m_mesh = world->GetMesh("torus");
		torus1->AddComponent<MaterialComponent>()->m_material = world->GetMaterial("metal");
		torus1->AddComponent<RigidBodyComponent>()->SetBoxCollider(.5f, .5f, .5f);
		torus1->AddComponent<EnemyShape>();

		Rotator* rotTorus = torus1->AddComponent<Rotator>();
		rotTorus->eulerDelta.x = 1.0f;
		rotTorus->eulerDelta.y = 1.0f;
	}
}
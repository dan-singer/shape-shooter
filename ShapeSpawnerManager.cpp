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
	if (!player) {
		player = World::GetInstance()->Find("Cam");
	}
	//update spawn timer
	spawnTimer += deltaTime;
	if (spawnTimer > timeUntilSpawn)
	{

		chooseShape();//spawn shape
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

void ShapeSpawnerManagerComponent::chooseShape()
{
	int type = rand() % 6;
	
	XMFLOAT3 shipPos = player->GetTransform()->GetPosition();
	XMFLOAT3 shipFor = player->GetTransform()->GetForward();
	//use to randomize where infront of the camera the shape spawns
	int randPosX = rand() % 5;
	int randPosY = rand() % 5;
	int randPosZ = rand() % 5;
	//This makes the x,y,and z values for the shape to spawn at, I left it out of a 
	//method because it would be easier to change the base value of 10 for one of them here
	float x = shipPos.x + shipFor.x * (10 + randPosX);
	float y = shipPos.y + shipFor.y * (10 + randPosY);
	float z = shipPos.z + shipFor.z * (10 + randPosZ);

	switch (type)
	{
	case 0:  
		spawnShape("cube", x,y,z);
		break;
	case 1:
		spawnShape("cone", x, y, z);
		break;
	case 2:
		spawnShape("cylinder", x, y, z);
		break;
	case 3:
		spawnShape("helix", x, y, z);
		break;
	case 4:
		spawnShape("sphere", x, y, z);
		break;
	case 5:
		spawnShape("torus", x, y, z);
		break;
	default:
		spawnShape("sphere", x, y, z);
		break;
	}
}

void ShapeSpawnerManagerComponent::spawnShape(std::string shape, float x, float y, float z)
{
	World* world = World::GetInstance();
	//shape1 is the entity for the shape because shape is the string name for it
	Entity* shape1 = world->Instantiate("shape");
	shape1->GetTransform()->SetPosition(XMFLOAT3(x, y, z));
	shape1->AddComponent<MeshComponent>()->m_mesh = world->GetMesh(shape);
	shape1->AddComponent<MaterialComponent>()->m_material = world->GetMaterial("metal");
	shape1->AddComponent<RigidBodyComponent>()->SetBoxCollider(.5f, .5f, .5f);
	shape1->AddComponent<EnemyShape>()->OnLose = OnLose;
	SoundComponent* sc = shape1->AddComponent<SoundComponent>();
	sc->SetSound(world->GetSound("hitFail"));
	sc->SetVolume(0.5f);

	Rotator* rot = shape1->AddComponent<Rotator>();
	rot->eulerDelta.x = 1.0f;
	rot->eulerDelta.y = 1.0f;
}
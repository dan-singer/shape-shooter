#include "EnemyShape.h"
#include "Entity.h"
#include "Mesh.h"
#include "CameraComponent.h"
#include <DirectXMath.h>
#include "TimedDestructor.h"
#include "UITextComponent.h"

using namespace DirectX;
void EnemyShape::Start()
{
	m_scoreText = World::GetInstance()->Find("Score")->GetComponent<UITextComponent>();
	m_soundComponent = GetOwner()->GetComponent<SoundComponent>();
}

void EnemyShape::Tick(float deltaTime)
{
	World* world = World::GetInstance();
	Entity* player = world->m_mainCamera->GetOwner();
	// Move towards the player (the camera)
	XMFLOAT3 posData = GetOwner()->GetTransform()->GetPosition();
	XMFLOAT3 playerPosData = player->GetTransform()->GetPosition();
	XMVECTOR translation = XMVector3Normalize(XMVectorSubtract(XMLoadFloat3(&playerPosData), XMLoadFloat3(&posData))) * m_trackSpeed * deltaTime;
	XMFLOAT3 translationData;
	XMStoreFloat3(&translationData, translation);
	GetOwner()->GetTransform()->Translate(translationData);
}

void EnemyShape::OnCollisionBegin(Entity* other)
{
	if (GetOwner()->GetMesh() == other->GetMesh()) {

		World* world = World::GetInstance();
		// Spawn an explosion effect
		Entity* explosion = world->Instantiate("explosion");
		explosion->AddComponent<EmitterComponent>()->Init("Assets/Particles/Explosion.json", world->GetDevice());
		explosion->AddComponent<MaterialComponent>()->m_material = world->GetMaterial("particle");
		SoundComponent* sc = explosion->AddComponent<SoundComponent>();
		sc->SetSound(world->GetSound("explosion"));
		sc->Play();
		explosion->AddComponent<TimedDestructor>()->SetDuration(2.0f);
		explosion->GetTransform()->SetPosition(GetOwner()->GetTransform()->GetPosition());

		int score = std::stoi(m_scoreText->m_text);
		score++;
		m_scoreText->m_text = std::to_string(score);

		World::GetInstance()->Destroy(other);
		World::GetInstance()->Destroy(GetOwner());
	}
	else {
		m_soundComponent->Play();
	}
}


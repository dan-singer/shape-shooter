#include "EnemyShape.h"
#include "Entity.h"
#include "Mesh.h"
#include "CameraComponent.h"
#include <DirectXMath.h>

using namespace DirectX;
void EnemyShape::Start()
{

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
	// For now, just destroy both objects if the shapes match
	if (GetOwner()->GetMesh() == other->GetMesh()) {
		World::GetInstance()->Destroy(other);
		World::GetInstance()->Destroy(GetOwner());
	}
}

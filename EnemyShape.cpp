#include "EnemyShape.h"
#include "Entity.h"
#include "Mesh.h"
void EnemyShape::Start()
{
}

void EnemyShape::Tick(float deltaTime)
{
}

void EnemyShape::OnCollisionBegin(Entity* other)
{
	// For now, just destroy both objects if the shapes match
	if (GetOwner()->GetMesh() == other->GetMesh()) {
		World::GetInstance()->Destroy(other);
		World::GetInstance()->Destroy(GetOwner());
	}
}

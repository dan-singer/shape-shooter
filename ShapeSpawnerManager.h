#pragma once
#include "Component.h"
#include <stdlib.h>
#include <time.h>
#include <DirectXMath.h>

class ShapeSpawnerManagerComponent : public Component
{
private:
	float spawnTimer = 0;
	float timeUntilSpawn = 0;
public:
	ShapeSpawnerManagerComponent(Entity* entity);
	void spawnShapes();
	virtual void Tick(float deltaTime) override;
	virtual void Start() override;
};


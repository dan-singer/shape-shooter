#pragma once
#include "Component.h"
#include <stdlib.h>
#include <time.h>
#include <DirectXMath.h>
#include <functional>

typedef std::function<void()> Action;

class ShapeSpawnerManagerComponent : public Component
{
private:
	float spawnTimer = 0;
	float timeUntilSpawn = 0;
	Entity* player = nullptr;
public:
	ShapeSpawnerManagerComponent(Entity* entity);
	void spawnShape(std::string shape, float x, float y, float z);
	void chooseShape();
	virtual void Tick(float deltaTime) override;
	virtual void Start() override;
	Action OnLose = nullptr;

};


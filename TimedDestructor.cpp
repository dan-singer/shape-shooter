#include "TimedDestructor.h"
#include "World.h"

void TimedDestructor::Start()
{
	m_timer = 0.0f;
}

void TimedDestructor::Tick(float deltaTime)
{
	m_timer += deltaTime;
	if (m_timer >= m_duration) {
		World::GetInstance()->Destroy(GetOwner());
	}
}

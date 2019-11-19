#include "GameManagerComponent.h"

void GameManagerComponent::AddScore(int _score)
{
	m_score += _score;
}

int* GameManagerComponent::GetScore()
{
	return m_score;
}

void GameManagerComponent::Start()
{
}

void GameManagerComponent::Tick(float deltaTime)
{
}

void GameManagerComponent::UpdateUI()
{
	//Julian Code Here
}

#include "framework.h"
#include "GameManager.h"

GameManager::~GameManager()
{
}

void GameManager::Release()
{
}

void GameManager::Update()
{
	if (INPUT->KeyDown(VK_F1))
	{
		DEBUG_MODE = !DEBUG_MODE;
	}
}

void GameManager::LateUpdate()
{
}

void GameManager::Render()
{
}

void GameManager::ResizeScreen()
{
}

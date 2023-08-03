#include "stdafx.h"
#include "Chest.h"
#include "ObjectManager.h"

void ObjectManager::Init()
{
}

void ObjectManager::Release()
{
}

void ObjectManager::Update()
{
	for (auto& chest : chests)
		chest->Update();
}

void ObjectManager::LateUpdate()
{
}

void ObjectManager::Render()
{
	for (auto& chest : chests)
		chest->Render();
}

void ObjectManager::AddChest(Chest* chest)
{
	chests.emplace_back(chest);
}

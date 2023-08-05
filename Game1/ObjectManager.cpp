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
	// ¸ÊÀ» ³Ñ¾î°¬À¸¸é chest¸¦ »èÁ¦
	chests.erase(
		std::remove_if
		(
			chests.begin(),
			chests.end(),
			[](Chest* chest) 
			{ 
				if (chest->GetIsCleared())
				{
					delete chest;
					return true;
				}
				else return false; 
			}
		),
		chests.end()
	);

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

void ObjectManager::ClearChests()
{
	for (auto& chest : chests)
		chest->SetCleared();
}

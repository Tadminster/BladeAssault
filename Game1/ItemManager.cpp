#include "stdafx.h"
#include "Item.h"
#include "ItemManager.h"

void ItemManager::Init()
{
}

void ItemManager::Release()
{
}

void ItemManager::Update()
{
	// Active �� ������ ����
	dropItems.erase(
		std::remove_if
		(
			dropItems.begin(),
			dropItems.end(),
			[](Item* item)
			{
				if (item->isActive)
				{
					delete item;
					return true;
				}
				else return false;
			}
		),
		dropItems.end()
	);

	for (auto& items : dropItems)
		items->Update();
}

void ItemManager::LateUpdate()
{
}

void ItemManager::Render()
{
	for (auto& items : dropItems)
		items->Render();
}

void ItemManager::AddItem(Item* item)
{
	this->dropItems.emplace_back(item);
}

void ItemManager::ActivateAllItem()
{
	// �������� ��� Active ���·� ����
	// active ������ �������� update���� ��ü�� delete �ϰ� vector���� ����
	for (auto& item : dropItems)
		item->isActive = true;

}

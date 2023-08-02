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
	// Active 된 아이템 삭제
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
	// 아이템을 모두 Active 상태로 변경
	// active 상태인 아이템은 update에서 객체를 delete 하고 vector에서 제거
	for (auto& item : dropItems)
		item->isActive = true;

}

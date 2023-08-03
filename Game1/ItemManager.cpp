#include "stdafx.h"
#include "Item.h"

// NORMAL
#include "cottonGloves.h"
#include "dart.h"
#include "ironBullet.h"
#include "leatherBelt.h"
#include "normalGear.h"
#include "oldSneakers.h"
#include "starBadge.h"

// RARE
#include "championBelt.h"
#include "grip.h"
#include "icepick.h"
#include "magicSword.h"
#include "rareGear.h"

// EPIC
#include "candle.h"
#include "epicGear.h"
#include "reinforcedChampionBelt.h"
#include "reinforcedGrip.h"

// LEGENDARY
#include "legendaryGear.h"


#include "ItemManager.h"

void ItemManager::Init()
{
	// ������ ������ �ʱ�ȭ
	// normal
	itemData.emplace(1, new cottonGloves());
	itemData.emplace(2, new dart());
	itemData.emplace(3, new ironBullet());
	itemData.emplace(4, new leatherBelt());
	itemData.emplace(5, new normalGear());
	itemData.emplace(6, new oldSneakers());
	itemData.emplace(7, new starBadge());

	// rare
	itemData.emplace(101, new championBelt());
	itemData.emplace(102, new magicSword());
	itemData.emplace(103, new icepick());
	itemData.emplace(104, new grip());
	itemData.emplace(105, new rareGear());

	// epic
	itemData.emplace(201, new candle());
	itemData.emplace(202, new epicGear());
	itemData.emplace(203, new reinforcedChampionBelt());
	itemData.emplace(204, new reinforcedGrip());

	// legendary
	itemData.emplace(301, new legendaryGear());

	// ����
	gradeCriteria[ItemGrade::NORMAL] = 0;
	gradeCriteria[ItemGrade::RARE] = 100;
	gradeCriteria[ItemGrade::EPIC] = 200;
	gradeCriteria[ItemGrade::LEGENDARY] = 300;

	// ������
	itemSize[ItemGrade::NORMAL] = 3;
	itemSize[ItemGrade::RARE] = 4;
	itemSize[ItemGrade::EPIC] = 3;
	itemSize[ItemGrade::LEGENDARY] = 0;
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
					//delete item;
					return true;
				}
				else return false;
			}
		),
		dropItems.end()
	);

	for (auto& item : dropItems)
		item->Update();
}

void ItemManager::LateUpdate()
{
}

void ItemManager::Render()
{
	for (auto& item : dropItems)
		item->Render();
}

void ItemManager::CreateItem(int itemGrade[3], Vector2 spawnPos)
{
	int itemNum[3] = { 0, 0, 0 };
	while (true)
	{
		// ���� itemNum �̱�
		for (int i = 0; i < 3; i++)
		{
			// ���� ����(
			// ���� + 1, 
			// ���� + ������)
			if (itemGrade[i] == ItemGrade::NORMAL)
				itemNum[i] = RANDOM->Int(
					gradeCriteria[ItemGrade::NORMAL] + 1, 
					gradeCriteria[ItemGrade::NORMAL] + itemSize[ItemGrade::NORMAL]);
			else if (itemGrade[i] == ItemGrade::RARE)
				itemNum[i] = RANDOM->Int(
					gradeCriteria[ItemGrade::RARE] + 1, 
					gradeCriteria[ItemGrade::RARE] + itemSize[ItemGrade::RARE]);
			else if (itemGrade[i] == ItemGrade::EPIC)
				itemNum[i] = RANDOM->Int(
					gradeCriteria[ItemGrade::EPIC] + 1, 
					gradeCriteria[ItemGrade::EPIC] + itemSize[ItemGrade::EPIC]);
			else if (itemGrade[i] == ItemGrade::LEGENDARY)
				itemNum[i] = RANDOM->Int(
					gradeCriteria[ItemGrade::LEGENDARY], 
					gradeCriteria[ItemGrade::LEGENDARY] + itemSize[ItemGrade::LEGENDARY]);
		}

		// itemNum�� �ߺ����� �ʴ��� Ȯ��
		if (itemNum[0] != itemNum[1] && itemNum[0] != itemNum[2] && itemNum[1] != itemNum[2])
			break;
	}

	// item ����
	Item* itemLeft = itemData.at(itemNum[0]);
	Item* itemMiddle = itemData.at(itemNum[1]);
	Item* itemRight = itemData.at(itemNum[2]);

	// item ��ġ ����
	itemLeft->SetPosition(spawnPos);
	itemMiddle->SetPosition(spawnPos + LEFT * 175.0f);
	itemRight->SetPosition(spawnPos + RIGHT * 175.0f);

	// itemManager�� �߰�
	dropItems.emplace_back(itemLeft);
	dropItems.emplace_back(itemMiddle);
	dropItems.emplace_back(itemRight);
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

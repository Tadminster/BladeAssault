#include "stdafx.h"
#include "Item.h"

// NORMAL
#include "bearhat.h"
#include "cottonGloves.h"
#include "dart.h"
#include "duracell.h"
#include "ironBullet.h"
#include "leatherBelt.h"
#include "normalGear.h"
#include "oldSneakers.h"
#include "starBadge.h"
#include "woodenShield.h"


// RARE
#include "championBelt.h"
#include "grip.h"
#include "icepick.h"
#include "magicSword.h"
#include "rareGear.h"

// EPIC
#include "boxingGloves.h"
#include "candle.h"
#include "epicGear.h"
#include "reinforcedChampionBelt.h"
#include "reinforcedGrip.h"
#include "rogueMask.h"
#include "silverAxe.h"

// LEGENDARY
#include "firstAidKit.h"
#include "goldGrip.h"
#include "heroSword.h"
#include "legendaryChampionBelt.h"
#include "legendaryGear.h"
#include "lv3helmet.h"
#include "ringOfGiant.h"
#include "runeStone.h"
#include "trinity.h"
#include "hourGlass.h"


#include "ItemManager.h"

void ItemManager::Init()
{
	// 아이템 데이터 초기화
	// normal
	itemData.emplace(1, new bearhat());
	itemData.emplace(2, new cottonGloves());
	itemData.emplace(3, new dart());
	itemData.emplace(4, new duracell());
	itemData.emplace(5, new ironBullet());
	itemData.emplace(6, new leatherBelt());
	itemData.emplace(7, new normalGear());
	itemData.emplace(8, new oldSneakers());
	itemData.emplace(9, new starBadge());
	itemData.emplace(10, new woodenShield());

	// rare
	itemData.emplace(101, new championBelt());
	itemData.emplace(102, new magicSword());
	itemData.emplace(103, new icepick());
	itemData.emplace(104, new grip());
	itemData.emplace(105, new rareGear());

	// epic
	itemData.emplace(201, new boxingGloves());
	itemData.emplace(202, new candle());
	itemData.emplace(203, new epicGear());
	itemData.emplace(204, new reinforcedChampionBelt());
	itemData.emplace(205, new reinforcedGrip());
	itemData.emplace(206, new rogueMask());
	itemData.emplace(207, new silverAxe());

	// legendary
	itemData.emplace(301, new firstAidKit());
	itemData.emplace(302, new goldGrip());
	itemData.emplace(303, new heroSword());
	itemData.emplace(304, new legendaryChampionBelt());
	itemData.emplace(305, new legendaryGear());
	itemData.emplace(306, new lv3helmet());
	itemData.emplace(307, new ringOfGiant());
	itemData.emplace(308, new runeStone());
	itemData.emplace(309, new trinity());
	itemData.emplace(310, new hourGlass());

	// 기준
	gradeCriteria[ItemGrade::NORMAL] = 0;
	gradeCriteria[ItemGrade::RARE] = 100;
	gradeCriteria[ItemGrade::EPIC] = 200;
	gradeCriteria[ItemGrade::LEGENDARY] = 300;

	// 사이즈
	itemSize[ItemGrade::NORMAL] = 10;
	itemSize[ItemGrade::RARE] = 5;
	itemSize[ItemGrade::EPIC] = 7;
	itemSize[ItemGrade::LEGENDARY] = 10;
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
		// 랜덤 itemNum 뽑기
		for (int i = 0; i < 3; i++)
		{
			// 랜덤 범위(
			// 기준 + 1, 
			// 기준 + 사이즈)
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
					gradeCriteria[ItemGrade::LEGENDARY] + 1, 
					gradeCriteria[ItemGrade::LEGENDARY] + itemSize[ItemGrade::LEGENDARY]);
		}

		// itemNum이 중복되지 않는지 확인
		if (itemNum[0] != itemNum[1] && itemNum[0] != itemNum[2] && itemNum[1] != itemNum[2])
			break;
	}

	// item 생성
	Item* itemLeft = itemData.at(itemNum[0]);
	Item* itemMiddle = itemData.at(itemNum[1]);
	Item* itemRight = itemData.at(itemNum[2]);

	// item 위치 설정
	itemLeft->SetPosition(spawnPos);
	itemMiddle->SetPosition(spawnPos + LEFT * 175.0f);
	itemRight->SetPosition(spawnPos + RIGHT * 175.0f);

	// itemManager에 추가
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
	// 아이템을 모두 Active 상태로 변경
	// active 상태인 아이템은 update에서 객체를 delete 하고 vector에서 제거
	for (auto& item : dropItems)
		item->isActive = true;

}

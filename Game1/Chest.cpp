#include "stdafx.h"
#include "Creature.h"
#include "Player.h"
#include "ItemManager.h"
#include "Chest.h"

Chest::Chest()
{
	collider				= new ObRect();
	collider->pivot			= OFFSET_B;
	collider->scale			= Vector2(100, 100);
	collider->isFilled		= false;
	collider->SetWorldPos(Vector2());

	presskey				= new ObImage(L"chest_Press.png");
	presskey->pivot			= OFFSET_B;
	presskey->SetParentRT(*GM->player->GetCollider());
	presskey->SetLocalPosY(-collider->scale.y * 0.45f);
	presskey->scale.x		= presskey->imageSize.x;
	presskey->scale.y		= presskey->imageSize.y;
	//presskey->ChangeAnim(ANIMSTATE::LOOP, 0.15f, true);
}

Chest::~Chest()
{
	delete collider;
	delete locked;
	delete unlocking;
	delete unlocked;
}

void Chest::Init()
{
}

void Chest::Update()
{

	collider->Update();
	if (state == ChestState::LOCKED)
	{
		if (collider->Intersect(GM->player->GetCollider()))
		{

			presskey->Update();
			if (INPUT->KeyDown('F'))
			{
				state = ChestState::UNlOCKING;
			}
		}
		locked->Update();
	}
	else if (state == ChestState::UNlOCKING)
	{
		unlocking->Update();

		if (unlocking->frame.x == unlocking->maxFrame.x - 1)
		{
			state = ChestState::UNLOCKED;
			CreateItem();
		}
	}
	else if (state == ChestState::UNLOCKED)
	{
		unlocked->Update();
	}
}

void Chest::Render()
{
	if (GM->DEBUG_MODE)
		collider->Render();

	if (state == ChestState::LOCKED)
	{
		if (collider->Intersect(GM->player->GetCollider()))
		{
			presskey->Render();
		}
		locked->Render();
	}
	else if (state == ChestState::UNlOCKING)
	{
		unlocking->Render();
	}
	else if (state == ChestState::UNLOCKED)
	{
		unlocked->Render();
	}
}

void Chest::CreateItem()
{
	int itemGrade[3];

	// 1~100 사이의 랜덤값을 3개 생성
	itemGrade[0] = RANDOM->Int(1, 100);
	itemGrade[1] = RANDOM->Int(1, 100);
	itemGrade[2] = RANDOM->Int(1, 100);

	// 아이템의 등급을 정함
	for (int i = 0; i < 3; i++)
	{
		if (itemGrade[i] <= gradeRate[ItemGrade::NORMAL])
			itemGrade[i] = ItemGrade::NORMAL;
		else if (itemGrade[i] <= gradeRate[ItemGrade::NORMAL] + gradeRate[ItemGrade::RARE])
			itemGrade[i] = ItemGrade::RARE;
		else if (itemGrade[i] <= gradeRate[ItemGrade::NORMAL] + gradeRate[ItemGrade::RARE] + gradeRate[ItemGrade::EPIC])
			itemGrade[i] = ItemGrade::EPIC;
		else
			itemGrade[i] = ItemGrade::LEGENDARY;
	}

	// 아이템을 생성함수 호출
	GM->item->CreateItem(itemGrade, collider->GetWorldPos());
}
#include "stdafx.h"
#include "Creature.h"
#include "Player.h"
#include "Chest.h"

Chest::Chest()
{
	collider				= new ObRect();
	collider->pivot			= OFFSET_B;
	collider->scale			= Vector2(100, 100);
	collider->isFilled		= false;
	collider->SetWorldPos(Vector2());

	presskey				= new ObImage(L"chest_PressE.png");
	presskey->pivot			= OFFSET_B;
	presskey->SetParentRT(*GM->player->GetCollider());
	presskey->SetLocalPosY(-collider->scale.y * 0.3f);
	presskey->scale.x		= presskey->imageSize.x;
	presskey->scale.y		= presskey->imageSize.y;
	//presskey->ChangeAnim(ANIMSTATE::LOOP, 0.15f, true);


	state = ChestState::LOCKED;
	isOpen  = false;
	isSpawn = false;
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
}

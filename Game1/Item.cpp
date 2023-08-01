#include "stdafx.h"
#include "Item.h"

Item::Item()
{
	collider = new ObRect();
	collider->pivot = OFFSET_B;
	collider->scale = Vector2(100, 100);
	collider->isFilled = false;
	collider->SetWorldPos(Vector2());

	presskey = new ObImage(L"chest_PressE.png");
	presskey->pivot = OFFSET_B;
	presskey->SetParentRT(*collider);
	presskey->SetLocalPosY(collider->scale.y * 1.2f);
	presskey->maxFrame.x = 1;
	presskey->maxFrame.y = 1;
	presskey->scale.x = presskey->imageSize.x / presskey->maxFrame.x;
	presskey->scale.y = presskey->imageSize.y / presskey->maxFrame.y;
	presskey->ChangeAnim(ANIMSTATE::LOOP, 0.15f, true);


	state = ItemState::LOCKED;
	isOpen = false;
	isSpawn = false;
}

Item::~Item()
{
	delete collider;
	delete locked;
	delete unlocking;
	delete unlocked;
}

void Item::Init()
{
}

void Item::Update()
{

	collider->Update();
	if (state == ItemState::LOCKED)
	{
		if (collider->Intersect(GM->player->GetCollider()))
		{

			presskey->Update();
			if (INPUT->KeyDown('F'))
			{
				state = ItemState::UNlOCKING;
				Open();
			}
		}
		locked->Update();
	}
	else if (state == ItemState::UNlOCKING)
	{
		unlocking->Update();

		if (unlocking->frame.x == unlocking->maxFrame.x - 1)
		{
			state = ItemState::UNLOCKED;
			Spawn();
		}
	}
	else if (state == ItemState::UNLOCKED)
	{
		unlocked->Update();
	}
}

void Item::Render()
{
	if (GM->DEBUG_MODE)
		collider->Render();

	if (state == ItemState::LOCKED)
	{
		if (collider->Intersect(GM->player->GetCollider()))
		{
			presskey->Render();
		}
		locked->Render();
	}
	else if (state == ItemState::UNlOCKING)
	{
		unlocking->Render();
	}
	else if (state == ItemState::UNLOCKED)
	{
		unlocked->Render();
	}
}

void Item::Open()
{
}

void Item::Spawn()
{
}

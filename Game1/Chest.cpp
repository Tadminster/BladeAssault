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
	presskey->SetParentRT(*collider);
	presskey->SetLocalPosY(collider->scale.y * 1.2f);
	presskey->maxFrame.x	= 1;
	presskey->maxFrame.y	= 1;
	presskey->scale.x		= presskey->imageSize.x / presskey->maxFrame.x;
	presskey->scale.y		= presskey->imageSize.y / presskey->maxFrame.y;
	presskey->ChangeAnim(ANIMSTATE::LOOP, 0.15f, true);


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
				Open();
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
			Spawn();
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

void Chest::Open()
{
}

void Chest::Spawn()
{
}

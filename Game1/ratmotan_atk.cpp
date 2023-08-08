#include "stdafx.h"
#include "Creature.h"
#include "player.h"
#include "EffectManager.h"
#include "Projectile.h"
#include "ratmotan_atk.h"

ratmotan_atk::ratmotan_atk(
	Vector2 spawnPos,
	Vector2 dir,
	float speed,
	float range,
	float damage,
	int   penetration,
	float explosionRange)
{
	tag = DamageType::PENETRATION;

	collider = new ObRect();
	collider->SetWorldPos(spawnPos);
	collider->scale = Vector2(300, 200);
	collider->isFilled = false;

	collider_range = nullptr;

	skin = new ObImage(L"alpa.png");
	skin->SetParentRT(*collider);
	skin->maxFrame.x = 1;
	skin->maxFrame.y = 1;
	skin->scale.x = skin->imageSize.x / skin->maxFrame.x * 2;
	skin->scale.y = skin->imageSize.y / skin->maxFrame.y * 2;
	skin->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
	if (dir == LEFT) skin->reverseLR = true;

	this->dir = dir;
	this->speed = speed;
	this->range = range;
	this->damage = damage;
	this->penetration = penetration;
	traveledDistance = 0.f;
	shove = 350;
}

void ratmotan_atk::Update()
{
	Projectile::Update();
	//collider_range->Update();
}

void ratmotan_atk::Render()
{
	if (GM->DEBUG_MODE)
		collider->Render();
	skin->Render();
}

void ratmotan_atk::AfterEffect()
{
	ObImage* effect = new ObImage(L"fx_redHairRat_proj.png");

	effect->SetWorldPos(GM->player->GetPosition() + UP * 60.0f);
	effect->maxFrame.x = 9;
	effect->maxFrame.y = 1;
	effect->scale.x = effect->imageSize.x / effect->maxFrame.x * 2.0f;
	effect->scale.y = effect->imageSize.y / effect->maxFrame.y * 2.0f;
	effect->ChangeAnim(ANIMSTATE::ONCE, 0.07f);
	effect->color.w = 0.35f;
	if (dir == LEFT)
	{
		effect->reverseLR = true;
		effect->pivot = OFFSET_L;
	}
	else if (dir == RIGHT)
	{
		effect->pivot = OFFSET_R;
	}

	GM->fx->AddEffects(effect);
}

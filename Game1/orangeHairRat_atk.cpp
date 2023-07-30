#include "stdafx.h"
#include "Projectile.h"
#include "EffectManager.h"
#include "orangeHairRat_atk.h"

orangeHairRat_atk::orangeHairRat_atk(
	Vector2 spawnPos,
	Vector2 dir,
	float speed,
	float range,
	float damage,
	int   penetration,
	float explosionRange)
{
	tag = DamageType::NORMAL;

	collider = new ObRect();
	collider->SetWorldPos(spawnPos);
	collider->scale = Vector2(32, 32);
	collider->isFilled = false;

	collider_range = nullptr;

	skin = new ObImage(L"projectile_orageHairRat.png");
	skin->SetParentRT(*collider);
	skin->maxFrame.x = 6;
	skin->maxFrame.y = 1;
	skin->scale.x = skin->imageSize.x / skin->maxFrame.x * 2;
	skin->scale.y = skin->imageSize.y / skin->maxFrame.y * 2;
	skin->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	if (dir == LEFT) skin->reverseLR = true;

	this->dir = dir;
	this->speed = speed;
	this->range = range;
	this->damage = damage;
	this->penetration = penetration;
	traveledDistance = 0.f;
	shove = 350;
}

void orangeHairRat_atk::Update()
{
	Projectile::Update();
}

void orangeHairRat_atk::Render()
{
	Projectile::Render();
}

void orangeHairRat_atk::AfterEffect()
{
	ObImage* effect = new ObImage(L"fx_orangeHairRat_proj.png");

	effect->SetWorldPos(collider->GetWorldPos());
	effect->maxFrame.x = 5;
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

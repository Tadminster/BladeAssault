#include "stdafx.h"
#include "Projectile.h"
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
	//ObImage* afterImg = new ObImage(L"fireball_explosion.png");
	//afterImg->SetWorldPos(collider->GetWorldPos());
	//afterImg->maxFrame.x = 7;
	//afterImg->maxFrame.y = 1;
	//afterImg->scale.x = collider_range->scale.x;
	//afterImg->scale.y = collider_range->scale.y;
	//afterImg->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
	//afterImg->color.w = 0.4f;


	//GM->afterEffectManager.emplace_back(afterImg);
}

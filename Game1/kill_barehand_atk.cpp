#include "stdafx.h"
#include "Projectile.h"
#include "kill_barehand_atk.h"

kill_barehand_atk::kill_barehand_atk(
	Vector2 spawnPos,
	Vector2 dir,
	float speed,
	float range,
	float damage,
	int   penetration,
	float explosionRange)
{
	tag = DamageType::EXPLOSION;

	collider = new ObRect();
	collider->SetWorldPos(spawnPos);
	collider->scale = Vector2(16, 16);
	collider->isFilled = false;

	collider_range = new ObCircle();
	collider_range->SetParentRT(*collider);
	collider_range->scale.x = explosionRange;
	collider_range->scale.y = explosionRange;
	collider_range->isFilled = false;

	skin = new ObImage(L"projectile_kill_gun_ignition_fire.png");
	skin->SetParentRT(*collider);
	skin->maxFrame.x = 8;
	skin->maxFrame.y = 1;
	skin->scale.x = skin->imageSize.x / skin->maxFrame.x * 2;
	skin->scale.y = skin->imageSize.y / skin->maxFrame.y * 2;
	skin->ChangeAnim(ANIMSTATE::LOOP, 0.05f);
	if (dir == LEFT) skin->reverseLR = true;

	this->dir = dir;
	this->speed = speed;
	this->range = range;
	this->damage = damage;
	this->penetration = penetration;
	traveledDistance = 0.f;
	shove = 350;
}

void kill_barehand_atk::Update()
{
	Projectile::Update();
	//collider_range->Update();
}

void kill_barehand_atk::Render()
{
	Projectile::Render();/*
	if (GM->DEBUG_MODE)
		collider_range->Render();*/
}

void kill_barehand_atk::AfterEffect()
{
	ObImage* afterImg = new ObImage(L"fireball_explosion.png");
	afterImg->SetWorldPos(collider->GetWorldPos());
	afterImg->maxFrame.x = 7;
	afterImg->maxFrame.y = 1;
	afterImg->scale.x = collider_range->scale.x;
	afterImg->scale.y = collider_range->scale.y;
	afterImg->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
	afterImg->color.w = 0.4f;

	
	//GM->afterEffectManager.emplace_back(afterImg);
}

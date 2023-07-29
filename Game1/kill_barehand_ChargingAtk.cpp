#include "stdafx.h"
#include "Projectile.h"
#include "kill_barehand_ChargingAtk.h"

kill_barehand_ChargingAtk::kill_barehand_ChargingAtk(
	Vector2 spawnPos,
	Vector2 dir,
	float speed,
	float range,
	float damage,
	int   penetration,
	float explosionRange,
	int   critical)
{
	tag = DamageType::PENETRATION;
	
	collider = new ObRect();
	collider->SetWorldPos(spawnPos);
	collider->scale = Vector2(app.GetHalfWidth(), 75);
	collider->isFilled = false;

	collider_range = new ObCircle();
	collider_range->SetParentRT(*collider);
	collider_range->scale.x = explosionRange;
	collider_range->scale.y = explosionRange;
	collider_range->isFilled = false;

	skin = new ObImage(L"projectile_kill_gun_ignition_charge.png");
	skin->SetParentRT(*collider);
	skin->maxFrame.x = 6;
	skin->maxFrame.y = 1;
	skin->scale.x = skin->imageSize.x / skin->maxFrame.x * 2.5;
	skin->scale.y = skin->imageSize.y / skin->maxFrame.y;
	skin->ChangeAnim(ANIMSTATE::LOOP, 0.05f);
	
	if (dir == LEFT)
	{
		collider->pivot = OFFSET_R;
		skin-> pivot = OFFSET_R;
		skin->reverseLR = true;
	}
	else if (dir == RIGHT)
	{
		collider->pivot = OFFSET_L;
		skin->pivot = OFFSET_L;
		skin->reverseLR = false;
	}

	this->dir = dir;
	this->speed = speed;
	this->range = range;
	this->damage = damage;
	this->criticalChance = critical;
	this->penetration = penetration;
	traveledDistance = 0.f;
	shove = 350;
}

kill_barehand_ChargingAtk::~kill_barehand_ChargingAtk()
{
	delete collider;
	delete collider_range;
	delete skin;
}

void kill_barehand_ChargingAtk::Update()
{
	Projectile::Update();
	//collider_range->Update();
}

void kill_barehand_ChargingAtk::Render()
{
	Projectile::Render();/*
	if (GM->DEBUG_MODE)
		collider_range->Render();*/
}

void kill_barehand_ChargingAtk::AfterEffect()
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

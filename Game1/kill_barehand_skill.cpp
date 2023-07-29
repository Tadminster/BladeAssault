#include "stdafx.h"
#include "Projectile.h"
#include "kill_barehand_skill.h"

kill_barehand_skill::kill_barehand_skill(
	float scale,
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
	collider->scale = Vector2(250 * scale, 320 * scale);
	collider->isFilled = false;

	collider_range = new ObCircle();
	collider_range->SetParentRT(*collider);
	collider_range->scale.x = explosionRange;
	collider_range->scale.y = explosionRange;
	collider_range->isFilled = false;

	skin = new ObImage(L"fx_kill_axe_ignite_powerwave.png");

	skin->SetParentRT(*collider);
	skin->SetLocalPosY(-collider->scale.y * 0.05);
	skin->maxFrame.x = 11;
	skin->maxFrame.y = 1;
	skin->scale.x = skin->imageSize.x / skin->maxFrame.x * 3 * scale;
	skin->scale.y = skin->imageSize.y / skin->maxFrame.y * 3 * scale;
	skin->ChangeAnim(ANIMSTATE::ONCE, 0.05f);
	if (dir == LEFT)
	{
		collider->pivot = OFFSET_RB;
		skin->pivot = OFFSET_RB;
		skin->SetLocalPosX(collider->scale.x * 0.4);
		skin->reverseLR = true;
	}
	else if (dir == RIGHT)
	{
		collider->pivot = OFFSET_LB;
		skin->pivot = OFFSET_LB;
		skin->SetLocalPosX(-collider->scale.x * 0.4);
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

kill_barehand_skill::~kill_barehand_skill()
{
	delete collider;
	delete collider_range;
	delete skin;
}

void kill_barehand_skill::Update()
{
	Projectile::Update();
	//collider_range->Update();
}

void kill_barehand_skill::Render()
{
	Projectile::Render();/*
	if (GM->DEBUG_MODE)
		collider_range->Render();*/
}

void kill_barehand_skill::AfterEffect()
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

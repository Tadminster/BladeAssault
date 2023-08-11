#include "stdafx.h"
#include "Projectile.h"
#include "EffectManager.h"
#include "kill_barehand_atk.h"

kill_barehand_atk::kill_barehand_atk(
	Vector2 spawnPos,
	Vector2 dir,
	float speed,
	float range,
	float damage,
	int   penetration,
	float explosionRange,
	int   critical)
{
	tag = DamageType::NORMAL;

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
	skin->maxFrame.x = 4;
	skin->maxFrame.y = 1;
	skin->scale.x = skin->imageSize.x / skin->maxFrame.x * 3;
	skin->scale.y = skin->imageSize.y / skin->maxFrame.y * 3;
	skin->ChangeAnim(ANIMSTATE::LOOP, 0.05f);
	if (dir == LEFT) skin->reverseLR = true;

	this->dir = dir;
	this->speed = speed;
	this->range = range;
	this->damage = damage;
	this->criticalChance = critical;
	this->penetration = penetration;
	traveledDistance = 0.0f;
	shove = 350;
}

kill_barehand_atk::~kill_barehand_atk()
{	
	delete collider;
	delete collider_range;
	delete skin;
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
	ObImage* effect = new ObImage(L"fx_kill_gun_ignition_fire.png");

	effect->SetWorldPos(collider->GetWorldPos());
	effect->maxFrame.x = 6;
	effect->maxFrame.y = 1;
	effect->scale.x = effect->imageSize.x / effect->maxFrame.x * 4.0f;
	effect->scale.y = effect->imageSize.y / effect->maxFrame.y * 4.0f;
	effect->ChangeAnim(ANIMSTATE::ONCE, 0.07f);
	effect->color.w = 0.4f;

	if (dir == LEFT) effect->reverseLR = true;

	GM->fx->AddEffects(effect);

	SOUND->Stop("kill_attack_hit");
	SOUND->Play("kill_attack_hit");
}

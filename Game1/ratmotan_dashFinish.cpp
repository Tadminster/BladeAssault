#include "stdafx.h"
#include "Projectile.h"
#include "EffectManager.h"
#include "ratmotan_dashFinish.h"

ratmotan_dashFinish::ratmotan_dashFinish(
	Vector2 spawnPos,
	Vector2 dir,
	float speed,
	float range,
	float damage,
	int   penetration,
	float explosionRange) :
	gravity(-500.f)
{
	tag = DamageType::PENETRATION;

	collider = new ObRect();
	collider->pivot = OFFSET_B;
	collider->SetWorldPos(spawnPos);
	collider->scale = Vector2(100, 200);
	collider->isFilled = false;

	collider_range = nullptr;

	skin = new ObImage(L"fx_ratmotan_dashFinish.png");
	skin->pivot = OFFSET_B;
	skin->SetParentRT(*collider);
	skin->maxFrame.x = 5;
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

void ratmotan_dashFinish::Update()
{
	CAM->position.x += (RANDOM->Int(0, 1) ? 2 : -2);
	CAM->position.y += (RANDOM->Int(0, 1) ? 1 : -1);

	Projectile::Update();
}

void ratmotan_dashFinish::Render()
{
	Projectile::Render();
}

void ratmotan_dashFinish::AfterEffect()
{
	//ObImage* effect = new ObImage(L"fx_greenHairRat_proj.png");

	//effect->SetWorldPos(collider->GetWorldPos());
	//effect->maxFrame.x = 10;
	//effect->maxFrame.y = 1;
	//effect->scale.x = effect->imageSize.x / effect->maxFrame.x * 4.0f;
	//effect->scale.y = effect->imageSize.y / effect->maxFrame.y * 4.0f;
	//effect->ChangeAnim(ANIMSTATE::ONCE, 0.07f);
	//effect->color.w = 0.35f;

	//GM->fx->AddEffects(effect);
}

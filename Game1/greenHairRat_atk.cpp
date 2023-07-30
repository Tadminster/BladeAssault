#include "stdafx.h"
#include "Projectile.h"
#include "EffectManager.h"
#include "greenHairRat_atk.h"

greenHairRat_atk::greenHairRat_atk(
	Vector2 spawnPos,
	Vector2 dir,
	float speed,
	float range,
	float damage,
	int   penetration,
	float explosionRange) :
	gravity(-500.f)
{
	tag = DamageType::NORMAL;

	collider = new ObRect();
	collider->SetWorldPos(spawnPos);
	collider->scale = Vector2(32, 32);
	collider->isFilled = false;

	collider_range = nullptr;

	skin = new ObImage(L"projectile_greenHairRat.png");
	skin->SetParentRT(*collider);
	skin->maxFrame.x = 8;
	skin->maxFrame.y = 1;
	skin->scale.x = skin->imageSize.x / skin->maxFrame.x * 3;
	skin->scale.y = skin->imageSize.y / skin->maxFrame.y * 3;
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

void greenHairRat_atk::Update()
{
	gravity += 750.f * DELTA;

	// 발사체 이동
	Vector2 velocity = (this->dir * this->speed);
	Vector2 verticalMove = DOWN * gravity;
	collider->MoveWorldPos((velocity + verticalMove) * DELTA);
	//collider->MoveWorldPos(verticalMove * DELTA);

	// 업데이트
	collider->Update();
	skin->Update();

	// 이동한 거리 계산
	traveledDistance += std::sqrt(std::pow(speed * DELTA, 2) + std::pow(speed * DELTA, 2));
}

void greenHairRat_atk::Render()
{
	Projectile::Render();
}

void greenHairRat_atk::AfterEffect()
{
	ObImage* effect = new ObImage(L"fx_greenRat_proj.png");

	effect->SetWorldPos(collider->GetWorldPos());
	effect->maxFrame.x = 10;
	effect->maxFrame.y = 1;
	effect->scale.x = effect->imageSize.x / effect->maxFrame.x * 4.0f;
	effect->scale.y = effect->imageSize.y / effect->maxFrame.y * 4.0f;
	effect->ChangeAnim(ANIMSTATE::ONCE, 0.07f);
	effect->color.w = 0.35f;

	GM->fx->AddEffects(effect);
}

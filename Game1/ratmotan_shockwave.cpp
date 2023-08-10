#include "stdafx.h"
#include "Projectile.h"
#include "EffectManager.h"
#include "ratmotan_shockwave.h"

ratmotan_shockwave::ratmotan_shockwave(
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
	collider->scale = Vector2(180, 100);
	collider->isFilled = false;

	collider_range = nullptr;

	skin = new ObImage(L"fx_ratmotan_shockwave2.png");
	skin->pivot = OFFSET_B;
	skin->SetParentRT(*collider);
	skin->maxFrame.x = 10;
	skin->maxFrame.y = 1;
	skin->scale.x = skin->imageSize.x / skin->maxFrame.x * 3;
	skin->scale.y = skin->imageSize.y / skin->maxFrame.y * 3;
	skin->ChangeAnim(ANIMSTATE::ONCE, 0.07f);
	if (dir == LEFT) skin->reverseLR = true;

	this->dir = dir;
	this->speed = speed;
	this->range = range;
	this->damage = damage;
	this->penetration = penetration;
	traveledDistance = 0.f;
	shove = 350;
}

void ratmotan_shockwave::Update()
{
	// 발사체 이동
	Vector2 velocity = this->dir * this->speed;
	collider->MoveWorldPos(velocity * DELTA);

	if (skin->frame.x >= 8 && collider->scale.x > 0)
	{
		collider->scale.x = 0;
		collider->scale.y = 0;
	}
	

	// 업데이트
	collider->Update();
	skin->Update();

	// 이동한 거리 계산
	traveledDistance += std::sqrt(std::pow(speed * DELTA, 2) + std::pow(speed * DELTA, 2));
}

void ratmotan_shockwave::Render()
{
	Projectile::Render();
}

void ratmotan_shockwave::AfterEffect()
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

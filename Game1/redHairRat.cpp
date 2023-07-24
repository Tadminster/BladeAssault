#include "stdafx.h"

#include "Projectile.h"
#include "redHairRat_atk.h"

#include "MonsterManager.h"

#include "Creature.h"
#include "Monster.h"
#include "redHairRat.h"

redHairRat::redHairRat()
{
	idle = new ObImage(L"redHairRat_idle.png");
	run = new ObImage(L"redHairRat_run.png");
	jump = new ObImage(L"redHairRat_jump.png");
	attack = new ObImage(L"redHairRat_attack.png");
    shadow = new ObImage(L"character_shadow.png");

    collider->pivot = OFFSET_B;
    collider->isFilled = false;
    collider->scale.x = 80;
    collider->scale.y = 110;
    //collider->SetWorldPos();

    idle->pivot = OFFSET_B;
    idle->SetParentRT(*collider);
    idle->SetLocalPosY(-collider->scale.y * 0.5);
    idle->maxFrame.x = 9;
    idle->maxFrame.y = 1;
    idle->scale.x = idle->imageSize.x / idle->maxFrame.x * 3;
    idle->scale.y = idle->imageSize.y / idle->maxFrame.y * 3;
    idle->ChangeAnim(ANIMSTATE::LOOP, 0.15f, true);

    run->pivot = OFFSET_B;
    run->SetParentRT(*collider);
    run->SetLocalPosY(-collider->scale.y * 0.5);
    run->maxFrame.x = 7;
    run->maxFrame.y = 1;
    run->scale.x = run->imageSize.x / run->maxFrame.x * 3;
    run->scale.y = run->imageSize.y / run->maxFrame.y * 3;
    run->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

    jump->pivot = OFFSET_B;
    jump->SetParentRT(*collider);
    jump->SetLocalPosY(-collider->scale.y * 0.5);
    jump->maxFrame.x = 2;
    jump->maxFrame.y = 2;
    jump->scale.x = jump->imageSize.x / jump->maxFrame.x * 3;
    jump->scale.y = jump->imageSize.y / jump->maxFrame.y * 3;
    jump->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

    attack->pivot = OFFSET_B;
    attack->SetParentRT(*collider);
    attack->SetLocalPosY(-collider->scale.y * 0.5);
    attack->maxFrame.x = 9;
    attack->maxFrame.y = 1;
    attack->scale.x = attack->imageSize.x / attack->maxFrame.x * 3;
    attack->scale.y = attack->imageSize.y / attack->maxFrame.y * 3;
    attack->ChangeAnim(ANIMSTATE::ONCE, 0.1f, true);

    shadow->pivot = OFFSET_B;
    shadow->SetParentRT(*collider);
    shadow->SetLocalPosY(-collider->scale.y * 0.4);
    shadow->maxFrame.x = 1;
    shadow->maxFrame.y = 1;
    shadow->scale.x = shadow->imageSize.x / shadow->maxFrame.x * 3;
    shadow->scale.y = shadow->imageSize.y / shadow->maxFrame.y * 3;
    shadow->color.w = 0.2f;
    shadow->ChangeAnim(ANIMSTATE::ONCE, 0.1f, true);

    CurrentState = State::IDLE;
    dir = LEFT;

    hp = 100;
    damage = 10;
    moveSpeed = 100;
    attackSpeed = 0.3f;
    attackFrame = 6;
    attackRange = 1;
}

redHairRat::~redHairRat()
{
	Monster::~Monster();
}

//void redHairRat::Init(Vector2 spawnPos)
//{
//	collider->isFilled = false;
//	collider->scale.x = 60;
//	collider->scale.y = 100;
//    collider->SetWorldPos(spawnPos);
//
//    idle->SetParentRT(*collider);
//    idle->SetLocalPosY(20);
//    idle->maxFrame.x = 6;
//    idle->maxFrame.y = 1;
//    idle->scale.x = idle->imageSize.x / idle->maxFrame.x * 3;
//    idle->scale.y = idle->imageSize.y / idle->maxFrame.y * 3;
//    idle->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);
//
//    run->SetParentRT(*collider);
//    run->SetLocalPosY(20);
//    run->maxFrame.x = 8;
//    run->maxFrame.y = 1;
//    run->scale.x = run->imageSize.x / run->maxFrame.x * 3;
//    run->scale.y = run->imageSize.y / run->maxFrame.y * 3;
//    run->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);
//
//    jump->SetParentRT(*collider);
//    jump->SetLocalPosY(20);
//    jump->maxFrame.x = 2;
//    jump->maxFrame.y = 2;
//    jump->scale.x = jump->imageSize.x / jump->maxFrame.x * 3;
//    jump->scale.y = jump->imageSize.y / jump->maxFrame.y * 3;
//    jump->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);
//
//    attack->SetParentRT(*collider);
//    attack->SetLocalPosY(20);
//    attack->maxFrame.x = 4;
//    attack->maxFrame.y = 1;
//    attack->scale.x = attack->imageSize.x / attack->maxFrame.x * 3;
//    attack->scale.y = attack->imageSize.y / attack->maxFrame.y * 3;
//    attack->ChangeAnim(ANIMSTATE::ONCE, 0.3f, true);
//
//    state = MonsterState::IDLE;
//    dir = LEFT;
//
//    hp = 100;
//    damage = 10;
//    speed = 100;
//    attackSpeed = 1.0f;
//    attackFrame = 6;
//
//}

void redHairRat::Update()
{
	Monster::Update();
}

void redHairRat::Render()
{
	Monster::Render();
}

void redHairRat::Attack()
{
    // 발사 위치 계산
    Vector2 spawnPos =
        collider->GetWorldPos()
        + dir * collider->scale.x * 0.8
        + UP * collider->scale.y * 0.8;

    // 탄생성
    redHairRat_atk* proj = new redHairRat_atk
    (
        spawnPos,										// 생성위치
        dir,										    // 각도
        5,   											// 발사체 속도
        attackRange, 									// 사거리
        damage,											// 공격력
        1,												// 관통력
        1												// 폭발범위
    );

    //벡터에 탄 push
    GM->monster->GetProjectiles().emplace_back(proj);
}

#include "stdafx.h"

#include "Projectile.h"
#include "redHairRat_atk.h"

#include "MonsterManager.h"

#include "Creature.h"
#include "Monster.h"
#include "ratmotan.h"

ratmotan::ratmotan()
{
    idle = new ObImage(L"ratmotan_idle.png");
    run = new ObImage(L"ratmotan_run.png");
    jump = new ObImage(L"ratmotan_jump.png");
    attack = new ObImage(L"ratmotan_powersmash.png");
    shadow = new ObImage(L"character_shadow.png");


    collider->pivot = OFFSET_B;
    collider->isFilled = false;
    collider->scale.x = 80;
    collider->scale.y = 110;

    //spawn->SetLocalPosX(-collider->scale.x * 0.1f);
    spawn->SetLocalPosY(-collider->scale.y * 0.5f);

    idle->pivot = OFFSET_B;
    idle->SetParentRT(*collider);
    idle->SetLocalPosY(-collider->scale.y * 0.7f);
    idle->maxFrame.x = 6;
    idle->maxFrame.y = 1;
    idle->scale.x = idle->imageSize.x / idle->maxFrame.x * 3.0f;
    idle->scale.y = idle->imageSize.y / idle->maxFrame.y * 3.0f;
    idle->color.w = 0.0f;
    idle->ChangeAnim(ANIMSTATE::LOOP, 0.15f, true);

    run->pivot = OFFSET_B;
    run->SetParentRT(*collider);
    run->SetLocalPosY(-collider->scale.y * 0.7f);
    run->maxFrame.x = 6;
    run->maxFrame.y = 1;
    run->scale.x = run->imageSize.x / run->maxFrame.x * 3.0f;
    run->scale.y = run->imageSize.y / run->maxFrame.y * 3.0f;
    run->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

    jump->pivot = OFFSET_B;
    jump->SetParentRT(*collider);
    jump->SetLocalPosY(-collider->scale.y * 0.7f);
    jump->maxFrame.x = 2;
    jump->maxFrame.y = 2;
    jump->scale.x = jump->imageSize.x / jump->maxFrame.x * 3.0f;
    jump->scale.y = jump->imageSize.y / jump->maxFrame.y * 3.0f;
    jump->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

    attack->pivot = OFFSET_B;
    attack->SetParentRT(*collider);
    attack->SetLocalPosY(-collider->scale.y * 0.7f);
    attack->maxFrame.x = 12;
    attack->maxFrame.y = 1;
    attack->scale.x = attack->imageSize.x / attack->maxFrame.x * 3.0f;
    attack->scale.y = attack->imageSize.y / attack->maxFrame.y * 3.0f;
    attack->ChangeAnim(ANIMSTATE::ONCE, 0.1f, true);

    shadow->pivot = OFFSET_B;
    shadow->SetParentRT(*collider);
    shadow->SetLocalPosY(-collider->scale.y * 0.4f);
    shadow->maxFrame.x = 1;
    shadow->maxFrame.y = 1;
    shadow->scale.x = shadow->imageSize.x / shadow->maxFrame.x * 4.0f;
    shadow->scale.y = shadow->imageSize.y / shadow->maxFrame.y * 4.0f;
    shadow->color.w = 0.2f;
    shadow->ChangeAnim(ANIMSTATE::ONCE, 0.1f, true);

    ui_frame_hp->SetLocalPosX(-collider->scale.x * 0.7f);
    ui_frame_hp->SetLocalPosY(collider->scale.y * 1.1f);
    ui_gauge_hp->SetLocalPosX(-collider->scale.x * 0.7f);
    ui_gauge_hp->SetLocalPosY(collider->scale.y * 1.1f);

    CurrentState = State::SPAWN;
    dir = LEFT;

    hp = 500;
    maxHp = 500;
    damage = 30;
    attackSpeed = 0.4f;
    attackFrame = 6;
    attackRange = 1;
    moveSpeed = 140;
    jumpSpeed = 700.0f;
    maxAttackDistance = 150;

    timeTakenToAttackOnce = 1.0f / attackSpeed;
}

//ratmotan::ratmotan(Vector2 spawnPos) : ratmotan()
//{
//    collider->SetWorldPos(spawnPos);
//}

ratmotan::~ratmotan()
{
}

void ratmotan::Update()
{
    Monster::Update();
}

void ratmotan::Render()
{
    Monster::Render();
}

void ratmotan::Attack()
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

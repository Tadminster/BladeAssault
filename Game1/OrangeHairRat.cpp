#include "stdafx.h"

#include "Projectile.h"
#include "orangeHairRat_atk.h"

#include "MonsterManager.h"

#include "Creature.h"
#include "Monster.h"
#include "orangeHairRat.h"

orangeHairRat::orangeHairRat()
{
    idle = new ObImage(L"orangeHairRat_idle.png");
    run = new ObImage(L"orangeHairRat_run.png");
    jump = new ObImage(L"orangeHairRat_jump.png");
    attack = new ObImage(L"orangeHairRat_attack.png");
    shadow = new ObImage(L"character_shadow.png");

    collider->pivot = OFFSET_B;
    collider->isFilled = false;
    collider->scale.x = 80;
    collider->scale.y = 110;
    //collider->SetWorldPos();

    spawn->SetLocalPosX(collider->scale.x * 0.1f);
    spawn->SetLocalPosY(-collider->scale.y * 0.1f);

    idle->pivot = OFFSET_B;
    idle->SetParentRT(*collider);
    idle->SetLocalPosY(-collider->scale.y * 0.5);
    idle->maxFrame.x = 7;
    idle->maxFrame.y = 1;
    idle->scale.x = idle->imageSize.x / idle->maxFrame.x * 3;
    idle->scale.y = idle->imageSize.y / idle->maxFrame.y * 3;
    idle->color.w = 0.0f;
    idle->ChangeAnim(ANIMSTATE::LOOP, 0.15f, true);


    run->pivot = OFFSET_B;
    run->SetParentRT(*collider);
    run->SetLocalPosY(-collider->scale.y * 0.5);
    run->maxFrame.x = 6;
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
    attack->maxFrame.x = 12;
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

    ui_frame_hp->SetLocalPosX(-collider->scale.x * 0.7f);
    ui_frame_hp->SetLocalPosY(collider->scale.y * 1.1f);
    ui_gauge_hp->SetLocalPosX(-collider->scale.x * 0.7f);
    ui_gauge_hp->SetLocalPosY(collider->scale.y * 1.1f);

    CurrentState = State::SPAWN;
    dir = LEFT;

    hp = 80;
    maxHp = 80;
    damage = 12;
    attackSpeed = 0.3f;
    attackFrame = 4;
    attackRange = 1000;
    moveSpeed = 100;
    jumpSpeed = 700.0f;
    maxAttackDistance = 450;

    timeTakenToAttackOnce = 1.0f / attackSpeed;
}

orangeHairRat::orangeHairRat(Vector2 spawnPos) : orangeHairRat()
{
    collider->SetWorldPos(spawnPos);
}

orangeHairRat::~orangeHairRat()
{

}

void orangeHairRat::Update()
{
    Monster::Update();
}

void orangeHairRat::Render()
{
    Monster::Render();
}

void orangeHairRat::Attack()
{
    // 발사 위치 계산
    Vector2 spawnPos =
        collider->GetWorldPos()
        + dir * collider->scale.x * 0.9
        + UP * collider->scale.y * 0.4;

    // 탄생성
    orangeHairRat_atk* proj = new orangeHairRat_atk
    (
        spawnPos,										// 생성위치
        dir,										    // 각도
        500,   											// 발사체 속도
        attackRange, 									// 사거리
        damage,											// 공격력
        1,												// 관통력
        1												// 폭발범위
    );

    //벡터에 탄 push
    GM->monster->GetProjectiles().emplace_back(proj);
}

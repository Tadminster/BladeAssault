#include "stdafx.h"

#include "Projectile.h"
#include "greenHairRat_atk.h"

#include "MonsterManager.h"

#include "Creature.h"
#include "Player.h"
#include "Monster.h"
#include "greenHairRat.h"

greenHairRat::greenHairRat()
{
    idle = new ObImage(L"greenHairRat_idle.png");
    run = new ObImage(L"greenHairRat_run.png");
    jump = new ObImage(L"greenHairRat_jump.png");
    attack = new ObImage(L"greenHairRat_attack.png");
    shadow = new ObImage(L"character_shadow.png");

    collider->pivot = OFFSET_B;
    collider->isFilled = false;
    collider->scale.x = 80;
    collider->scale.y = 110;
    //collider->SetWorldPos();

    //spawn->SetLocalPosX(-collider->scale.x * 0.1f);
    spawn->SetLocalPosY(-collider->scale.y * 0.5f);

    idle->pivot = OFFSET_B;
    idle->SetParentRT(*collider);
    idle->SetLocalPosY(-collider->scale.y * 0.5f);
    idle->maxFrame.x = 6;
    idle->maxFrame.y = 1;
    idle->scale.x = idle->imageSize.x / idle->maxFrame.x * 3.0f;
    idle->scale.y = idle->imageSize.y / idle->maxFrame.y * 3.0f;
    idle->color.w = 0.0f;
    idle->ChangeAnim(ANIMSTATE::LOOP, 0.15f, true);


    run->pivot = OFFSET_B;
    run->SetParentRT(*collider);
    run->SetLocalPosY(-collider->scale.y * 0.5f);
    run->maxFrame.x = 9;
    run->maxFrame.y = 1;
    run->scale.x = run->imageSize.x / run->maxFrame.x * 3.0f;
    run->scale.y = run->imageSize.y / run->maxFrame.y * 3.0f;
    run->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

    jump->pivot = OFFSET_B;
    jump->SetParentRT(*collider);
    jump->SetLocalPosY(-collider->scale.y * 0.5f);
    jump->maxFrame.x = 2;
    jump->maxFrame.y = 2;
    jump->scale.x = jump->imageSize.x / jump->maxFrame.x * 3.0f;
    jump->scale.y = jump->imageSize.y / jump->maxFrame.y * 3.0f;
    jump->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

    attack->pivot = OFFSET_B;
    attack->SetParentRT(*collider);
    attack->SetLocalPosY(-collider->scale.y * 0.5f);
    attack->maxFrame.x = 16;
    attack->maxFrame.y = 1;
    attack->scale.x = attack->imageSize.x / attack->maxFrame.x * 3.0f;
    attack->scale.y = attack->imageSize.y / attack->maxFrame.y * 3.0f;
    attack->ChangeAnim(ANIMSTATE::ONCE, 0.1f, true);

    shadow->pivot = OFFSET_B;
    shadow->SetParentRT(*collider);
    shadow->SetLocalPosY(-collider->scale.y * 0.4f);
    shadow->maxFrame.x = 1;
    shadow->maxFrame.y = 1;
    shadow->scale.x = shadow->imageSize.x / shadow->maxFrame.x * 3.0f;
    shadow->scale.y = shadow->imageSize.y / shadow->maxFrame.y * 3.0f;
    shadow->color.w = 0.2f;
    shadow->ChangeAnim(ANIMSTATE::ONCE, 0.1f, true);

    ui_frame_hp->SetLocalPosX(-collider->scale.x * 0.7f);
    ui_frame_hp->SetLocalPosY(collider->scale.y * 1.1f);
    ui_gauge_hp->SetLocalPosX(-collider->scale.x * 0.7f);
    ui_gauge_hp->SetLocalPosY(collider->scale.y * 1.1f);

    name = "greenHairRat";
    CurrentState = State::SPAWN;
    dir = LEFT;


    hp = 70;
    maxHp = 70;
    damage = 15;
    attackSpeed = 0.25f;
    attackFrame = 7;
    attackRange = 1000;
    moveSpeed = 100;
    jumpSpeed = 700.0f;
    maxAttackDistance = 450;

    timeTakenToAttackOnce = 1.0f / attackSpeed;
}

//greenHairRat::greenHairRat(Vector2 spawnPos) : greenHairRat()
//{
//    collider->SetWorldPos(spawnPos);
//}

greenHairRat::~greenHairRat()
{

}

void greenHairRat::Update()
{
    Monster::Update();
}

void greenHairRat::Render()
{
    Monster::Render();
}

void greenHairRat::Attack()
{
    // 발사 위치 계산
    Vector2 spawnPos =
        collider->GetWorldPos()
        + dir * collider->scale.x * 0.5f
        + UP * collider->scale.y * 1.0f;

    // 플레이어와 거리에 따라 발사체 속도 조절
    float speedTemp = abs(this->collider->GetWorldPos().x - GM->player->GetCollider()->GetWorldPos().x) * 0.6f;

    // 탄생성
    greenHairRat_atk* proj = new greenHairRat_atk
    (
        spawnPos,										// 생성위치
        dir,										    // 각도
        speedTemp,   									// 발사체 속도
        attackRange, 									// 사거리
        damage,											// 공격력
        1,												// 관통력
        1												// 폭발범위
    );

    //벡터에 탄 push
    GM->monster->GetProjectiles().emplace_back(proj);
}

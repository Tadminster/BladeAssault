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
    
    //spawn->SetLocalPosX(-collider->scale.x * 0.1f);
    spawn->SetLocalPosY(-collider->scale.y * 0.5f);

    idle->pivot = OFFSET_B;
    idle->SetParentRT(*collider);
    idle->SetLocalPosY(-collider->scale.y * 0.5f);
    idle->maxFrame.x = 9;
    idle->maxFrame.y = 1;
    idle->scale.x = idle->imageSize.x / idle->maxFrame.x * 3;
    idle->scale.y = idle->imageSize.y / idle->maxFrame.y * 3;
    idle->color.w = 0.0f;
    idle->ChangeAnim(ANIMSTATE::LOOP, 0.15f, true);

    run->pivot = OFFSET_B;
    run->SetParentRT(*collider);
    run->SetLocalPosY(-collider->scale.y * 0.5f);
    run->maxFrame.x = 7;
    run->maxFrame.y = 1;
    run->scale.x = run->imageSize.x / run->maxFrame.x * 3;
    run->scale.y = run->imageSize.y / run->maxFrame.y * 3;
    run->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

    jump->pivot = OFFSET_B;
    jump->SetParentRT(*collider);
    jump->SetLocalPosY(-collider->scale.y * 0.5f);
    jump->maxFrame.x = 2;
    jump->maxFrame.y = 2;
    jump->scale.x = jump->imageSize.x / jump->maxFrame.x * 2.8;
    jump->scale.y = jump->imageSize.y / jump->maxFrame.y * 2.8;
    jump->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

    attack->pivot = OFFSET_B;
    attack->SetParentRT(*collider);
    attack->SetLocalPosY(-collider->scale.y * 0.5f);
    attack->maxFrame.x = 9;
    attack->maxFrame.y = 1;
    attack->scale.x = attack->imageSize.x / attack->maxFrame.x * 3;
    attack->scale.y = attack->imageSize.y / attack->maxFrame.y * 3;
    attack->ChangeAnim(ANIMSTATE::ONCE, 0.1f, true);

    shadow->pivot = OFFSET_B;
    shadow->SetParentRT(*collider);
    shadow->SetLocalPosY(-collider->scale.y * 0.4f);
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

    name = "redHairRat";
    CurrentState = State::SPAWN;
    dir = LEFT;

    hp = 100;
    maxHp = 100;
    damage = 10;
    attackSpeed = 0.4f;
    attackFrame = 6;
    attackRange = 1;
    moveSpeed = 100;
    jumpSpeed = 700.0f;
    maxAttackDistance = 150;

    timeTakenToAttackOnce = 1.0f / attackSpeed;
}

//redHairRat::redHairRat(Vector2 spawnPos) : redHairRat()
//{
//    collider->SetWorldPos(spawnPos);
//}

redHairRat::~redHairRat()
{
}

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
    // �߻� ��ġ ���
    Vector2 spawnPos =
        collider->GetWorldPos()
        + dir * collider->scale.x * 0.8
        + UP * collider->scale.y * 0.8;

    // ź����
    redHairRat_atk* proj = new redHairRat_atk
    (
        spawnPos,										// ������ġ
        dir,										    // ����
        5,   											// �߻�ü �ӵ�
        attackRange, 									// ��Ÿ�
        damage,											// ���ݷ�
        1,												// �����
        1												// ���߹���
    );

    //���Ϳ� ź push
    GM->monster->GetProjectiles().emplace_back(proj);
}

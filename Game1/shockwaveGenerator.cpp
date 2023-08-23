#include "stdafx.h"

#include "Projectile.h"
#include "ratmotan_shockwave.h"

#include "MonsterManager.h"

#include "Creature.h"
#include "Player.h"
#include "Monster.h"
#include "shockwaveGenerator.h"

shockwaveGenerator::shockwaveGenerator()
{
    idle    = nullptr;
    run     = nullptr;
    jump    = nullptr;
    attack  = nullptr;
    shadow  = nullptr;
    spawn   = nullptr;

    collider->pivot = OFFSET_B;
    collider->isFilled = false;
    collider->scale.x = 50;
    collider->scale.y = 50;

    name = "shockwaveGenerator";
    dmgTaken = MonsterDamageTaken::IMMUNE;
    CurrentState = State::RUN;
    dir = LEFT;

    hp = 10;
    maxHp = 10;
    damage = 15;
    attackSpeed = 3.0f;
    attackFrame = 7;
    attackRange = 1000;
    moveSpeed = 700;
    jumpSpeed = 0.0f;
    maxAttackDistance = 0;

    timeTakenToAttackOnce = 1.0f / attackSpeed;
}

shockwaveGenerator::~shockwaveGenerator()
{
}

void shockwaveGenerator::Update()
{
    lastPos = collider->GetWorldPos();

    CAM->position.x += (RANDOM->Int(0, 1) ? 1 : -1);
    CAM->position.y += (RANDOM->Int(0, 1) ? 1 : -1);

    // ���� �ε�ġ�� ���
    if (onWallSide)
    {
        hp = 0;
    }

    // ��� ó��
    if (hp == 0 && CurrentState != State::DIE)
    {
        CurrentState = State::DIE;
    }

    if (CurrentState == State::RUN)
    {
        Attack();

        collider->MoveWorldPos(dir * moveSpeed * DELTA);
        collider->Update();
    }
}

void shockwaveGenerator::Render()
{
    if (GM->DEBUG_MODE)
        collider->Render();
}

void shockwaveGenerator::Attack()
{
    float currentTime = TIMER->GetWorldTime();			// ����ð�
    float elapsedTime = currentTime - lastAttackTime;	// ����ð�

    if (elapsedTime >= timeTakenToAttackOnce)
    {
        // �߻� ��ġ ���
        Vector2 spawnPos = collider->GetWorldPos();

        // ź����
        ratmotan_shockwave* proj = new ratmotan_shockwave
        (
            spawnPos,										// ������ġ
            dir,										    // ����
            2,   									        // �߻�ü �ӵ�
            2, 									            // ��Ÿ�
            damage,											// ���ݷ�
            1,												// �����
            1												// ���߹���
        );

        //���Ϳ� ź push
        GM->monster->GetProjectiles().emplace_back(proj);

        // ���Ӱ��
        lastAttackTime = currentTime;
        timeTakenToAttackOnce = 1.0f / attackSpeed;

        return;
    }
    else return;
}

bool shockwaveGenerator::isDead() const
{
    if (CurrentState == State::DIE)
    {
        return true;
    }
    else return false;
}

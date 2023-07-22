#include "stdafx.h"
#include "Player.h"
#include "Monster.h"
#include "MonsterManager.h"
#include "Projectile.h"

Projectile::Projectile
(
    Vector2 spawnPos,
    Vector2 dir,
    float speed,
    float range,
    float damage,
    int   penetration
) :
    collider(new ObRect()),
    collider_range(new ObCircle()),
    skin(nullptr),
    dir(dir),
    speed(speed),
    range(range),
    damage(damage),
    penetration(penetration),
    traveledDistance(0.f),
    shove(300)
{
    collider->rotation.z = atanf(dir.y / dir.x);
    collider->scale.x = 10;
    collider->scale.y = 10;
    collider->isFilled = false;
    collider->SetWorldPos(spawnPos);

    //collider_range->SetParentRT(*collider);

    //skin->SetParentRT(*collider);
}

void Projectile::Update()
{
    // �߻�ü �̵�
    Vector2 velocity = (this->dir * this->speed);
    collider->MoveWorldPos(velocity * DELTA);

    // ������Ʈ
    collider->Update();
    skin->Update();

    // �̵��� �Ÿ� ���
    traveledDistance += std::sqrt(std::pow(speed * DELTA, 2) + std::pow(speed * DELTA, 2));
}

void Projectile::Render()
{
    skin->Render();

    if (GM->DEBUG_MODE)
        collider->Render();
}

bool Projectile::hasCollideWithMonster()
{
    // ��� ���͸� ��ȸ
    for (auto& enemy : GM->monster->GetEnemy())
    {
        // ���Ͱ� �߻�ü�� �浹������
        if (enemy->GetCollider()->Intersect(this->collider))
        {
            // ������ �浹������ �ִ��� ��
            for (auto& crashed : crash)
                if (crashed == enemy) return false;

            // ������ �� �浹���Ϳ� �߰�
            this->crash.emplace_back(enemy);
            // ���� ����Ƚ�� -1
            this->penetration--;

            // �߻�ü�� ������ Ÿ������ Ȯ��
            if (this->tag == DamageType::EXPLOSION)
            {

                for (auto& InRangeCheck : GM->monster->GetEnemy())
                {
                    // null check
                    if (collider_range) 
                    {
                        // ���Ͱ� ���� ���� �ȿ� ������� Ȯ��
                        if (InRangeCheck->GetCollider()->Intersect(this->collider_range))
                        {
                            if (InRangeCheck == enemy) continue;
                            // ���� ������ �׼�
                            InRangeCheck->actionsWhenDamaged(Vector4(-damage * 0.5, shove, 0, 0));
                        }
                    }


                }
            }
            // �浹 ����Ʈ
            AfterEffect();

            // ���� ������ �׼�
            enemy->actionsWhenDamaged(Vector4(-damage, shove, 0, 0));

            // ���� ����� ��ȯ
            if (penetration > 0) return false;
            else return true;
        }
    }

    return false;
}

bool Projectile::hasCollideWithPlayer()
{
    if (collider->Intersect(GM->player->GetCollider()))
    {
        // �浹 ����Ʈ
        AfterEffect();

        // �÷��̾� ������ �׼�
        GM->player->actionsWhenDamaged(-damage);

        return true;
    }

    return false;
}

void Projectile::AfterEffect()
{
}

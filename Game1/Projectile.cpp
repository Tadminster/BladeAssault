#include "stdafx.h"
#include "Creature.h"
#include "Player.h"
#include "Monster.h"
#include "MonsterManager.h"
#include "Projectile.h"

Projectile::Projectile
(
    float scale,
    Vector2 spawnPos,
    Vector2 dir,
    float speed,
    float range,
    float damage,
    int   penetration,
    int   critical
) :
    collider(new ObRect()),
    collider_range(new ObCircle()),
    dir(dir),
    speed(speed),
    range(range),
    damage(damage),
    penetration(penetration),
    traveledDistance(0.f),
    shove(300),
    criticalChance(critical)
{
}

Projectile::Projectile
(
    Vector2 spawnPos,
    Vector2 dir,
    float speed,
    float range,
    float damage,
    int   penetration,
    int   critical
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
    shove(300),
    criticalChance(critical)
{
}


Projectile::~Projectile()
{
	delete collider;
	delete collider_range;
	delete skin;
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
    // �߻�ü�� ���� Ÿ���̸�
    if (this->tag == DamageType::PENETRATION)
    {
        // ��� ���͸� ��ȸ
        for (auto& monster : GM->monster->GetEnemy())
        {
            // ���Ͱ� ���� ���� �ȿ� ������� Ȯ��
            if (monster->GetCollider()->Intersect(this->collider))
            {
                // ������ �浹������ �ִ��� ��
                for (auto& crashedMonster : crash)
                    if (crashedMonster == monster) return false;

                GM->player->SetMp(2);

                // �浹�� ���� ������
                {
                    // �浹 ���Ϳ� �߰�
                    this->crash.emplace_back(monster);

                    // ���� ������ �׼�
                    monster->actionsWhenDamaged(damage, shove, criticalChance);

                    // �浹 ����Ʈ
                    AfterEffect();
                }
            }
        }
    }
    // �׿��� Ÿ���̸�
    else
    {
        // ��� ���͸� ��ȸ
        for (auto& monster : GM->monster->GetEnemy())
        {
            // ���Ͱ� �߻�ü�� �浹������
            if (monster->GetCollider()->Intersect(this->collider))
            {
                // ������ �浹������ �ִ��� ��
                for (auto& crashedMonster : crash)
                    if (crashedMonster == monster) return false;

                // �浹�� ���� ������
                {
                    // �浹 ���Ϳ� �߰�
                    this->crash.emplace_back(monster);

                    // ���� ����Ƚ�� -1
                    this->penetration--;

                    // �߻�ü�� �븻 Ÿ���̸�
                    if (this->tag == DamageType::NORMAL)
                    {
                        // ���� ������ �׼�
                        monster->actionsWhenDamaged(damage, shove, criticalChance);

                        GM->player->SetMp(3);
                    }


                    // �߻�ü�� ���� Ÿ���̸� ������ �߰� ���ߵ�����
                    else if (this->tag == DamageType::EXPLOSION)
                    {
                        for (auto& InRangeCheck : GM->monster->GetEnemy())
                        {
                            // null check
                            if (collider_range)
                            {
                                // ���Ͱ� ���� ���� �ȿ� ������� Ȯ��
                                if (InRangeCheck->GetCollider()->Intersect(this->collider_range))
                                {
                                    if (InRangeCheck == monster) continue;
                                    // ���� ������ �׼�
                                    InRangeCheck->actionsWhenDamaged(damage, shove, criticalChance);
                                }
                            }
                        }
                    }

                    // �浹 ����Ʈ
                    AfterEffect();

                    // ������� ��������
                    if (penetration > 0)
                        return false;
                    // ������� 0�̸� �߻�ü ����
                    else
                    {
                        delete this;
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool Projectile::hasCollideWithPlayer()
{
    // �ǰݴ����� 0.3�ʰ� ������ �ʾ����� ������ ���� ����
    if (TIMER->GetWorldTime() < GM->player->timeOfDamaged + 0.3f)
    {
        return false;
    }

    if (collider->Intersect(GM->player->GetCollider()))
    {
        // �浹 ����Ʈ
        AfterEffect();

        // �÷��̾� ������ �׼�
        GM->player->actionsWhenDamaged(damage);

        // �߻�ü�� ���� Ÿ���̸� �������� ����
        if (this->tag == DamageType::PENETRATION)
        {
            return false;
        }
        else
        {
            // �׿ܸ� ����
            return true;
            delete this;
        }

    }

    return false;
}

bool Projectile::hasTraveledTooFar() const
{
    if (traveledDistance >= range)
    {
        return true;
    }
    return false;
}


void Projectile::AfterEffect()
{
}

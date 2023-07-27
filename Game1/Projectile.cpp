#include "stdafx.h"
#include "Creature.h"
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

                // �浹�� ���� ������
                {
                    // �浹 ���Ϳ� �߰�
                    this->crash.emplace_back(monster);

                    // ���� ������ �׼�
                    monster->actionsWhenDamaged(Vector4(-damage, shove, 0, 0));
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
                        monster->actionsWhenDamaged(Vector4(-damage, shove, 0, 0));
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
                                    InRangeCheck->actionsWhenDamaged(Vector4(-damage * 0.5, shove, 0, 0));
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
    if (collider->Intersect(GM->player->GetCollider()))
    {
        // �浹 ����Ʈ
        AfterEffect();

        // �÷��̾� ������ �׼�
        GM->player->actionsWhenDamaged(-damage);
        delete this;
        return true;
    }

    return false;
}

bool Projectile::hasTraveledTooFar() const
{
    if (traveledDistance >= range)
    {
        delete this;
        return true;
    }
    return false;
}

void Projectile::AfterEffect()
{
}

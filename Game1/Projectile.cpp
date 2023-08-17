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
    // 발사체 이동
    Vector2 velocity = (this->dir * this->speed);
    collider->MoveWorldPos(velocity * DELTA);

    // 업데이트
    collider->Update();
    skin->Update();

    // 이동한 거리 계산
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
    // 발사체가 관통 타입이면
    if (this->tag == DamageType::PENETRATION)
    {
        // 모든 몬스터를 순회
        for (auto& monster : GM->monster->GetEnemy())
        {
            // 몬스터가 공격 범위 안에 들었는지 확인
            if (monster->GetCollider()->Intersect(this->collider))
            {
                // 이전에 충돌한적이 있는지 비교
                for (auto& crashedMonster : crash)
                    if (crashedMonster == monster) return false;

                GM->player->SetMp(2);

                // 충돌한 적이 없으면
                {
                    // 충돌 벡터에 추가
                    this->crash.emplace_back(monster);

                    // 몬스터 데미지 액션
                    monster->actionsWhenDamaged(damage, shove, criticalChance);

                    // 충돌 이펙트
                    AfterEffect();
                }
            }
        }
    }
    // 그외의 타입이면
    else
    {
        // 모든 몬스터를 순회
        for (auto& monster : GM->monster->GetEnemy())
        {
            // 몬스터가 발사체와 충돌했으면
            if (monster->GetCollider()->Intersect(this->collider))
            {
                // 이전에 충돌한적이 있는지 비교
                for (auto& crashedMonster : crash)
                    if (crashedMonster == monster) return false;

                // 충돌한 적이 없으면
                {
                    // 충돌 벡터에 추가
                    this->crash.emplace_back(monster);

                    // 남은 관통횟수 -1
                    this->penetration--;

                    // 발사체가 노말 타입이면
                    if (this->tag == DamageType::NORMAL)
                    {
                        // 몬스터 데미지 액션
                        monster->actionsWhenDamaged(damage, shove, criticalChance);

                        GM->player->SetMp(3);
                    }


                    // 발사체가 폭발 타입이면 범위에 추가 폭발데미지
                    else if (this->tag == DamageType::EXPLOSION)
                    {
                        for (auto& InRangeCheck : GM->monster->GetEnemy())
                        {
                            // null check
                            if (collider_range)
                            {
                                // 몬스터가 폭발 범위 안에 들었는지 확인
                                if (InRangeCheck->GetCollider()->Intersect(this->collider_range))
                                {
                                    if (InRangeCheck == monster) continue;
                                    // 몬스터 데미지 액션
                                    InRangeCheck->actionsWhenDamaged(damage, shove, criticalChance);
                                }
                            }
                        }
                    }

                    // 충돌 이펙트
                    AfterEffect();

                    // 관통력이 남았으면
                    if (penetration > 0)
                        return false;
                    // 관통력이 0이면 발사체 삭제
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
    // 피격당한지 0.3초가 지나지 않았으면 데미지 받지 않음
    if (TIMER->GetWorldTime() < GM->player->timeOfDamaged + 0.3f)
    {
        return false;
    }

    if (collider->Intersect(GM->player->GetCollider()))
    {
        // 충돌 이펙트
        AfterEffect();

        // 플레이어 데미지 액션
        GM->player->actionsWhenDamaged(damage);

        // 발사체가 관통 타입이면 삭제하지 않음
        if (this->tag == DamageType::PENETRATION)
        {
            return false;
        }
        else
        {
            // 그외면 삭제
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

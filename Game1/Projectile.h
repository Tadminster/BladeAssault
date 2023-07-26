#pragma once
enum class DamageType
{
    NORMAL,
    EXPLOSION,
    PENETRATION
};

class Projectile
{
public:
    class ObRect* collider;
    class ObCircle* collider_range;
    class ObImage* skin;

    Vector2         dir;                    // 방향
    float           speed;                  // 속도
    int             damage;                 // 공격력
    int             penetration;            // 관통력
    float           range;                  // 사정거리
    float           shove;                  // 밀쳐내기 계수
    float           traveledDistance;       // 이동거리

    DamageType      tag;

    vector<class Monster*> crash;

public:
    Projectile() {};
    Projectile(Vector2 spawnPos, Vector2 dir, float speed, float range, float damage, int penetration);
    ~Projectile();  
    virtual void        Update();
    virtual void        Render();

    virtual bool        hasCollideWithMonster();
    bool                hasCollideWithPlayer();
    /* 탄이 이동한 거리가 range를 넘었는지 확인 */
    bool                hasTraveledTooFar() const;
    /* 탄의 관통횟수가 전부 소모되었는지 확인 */
    bool                hasPenetration() const { return penetration <= 0; }

    virtual void       AfterEffect();
};


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

    Projectile() = default;
    // @brief 발사체 생성자
    // @param spawnPos 발사체 스케일
    // @param spawnPos 발사체 생성 위치
    // @param dir 발사체 방향
    // @param speed 발사체 속도
    // @param range 발사체 사정거리
    // @param damage 발사체 데미지
    // @param penetration 관통력
    Projectile(float scale, Vector2 spawnPos, Vector2 dir, float speed, float range, float damage, int penetration);
    Projectile(Vector2 spawnPos, Vector2 dir, float speed, float range, float damage, int penetration);
    ~Projectile();  
    virtual void        Update();
    virtual void        Render();

    // @brief 플레이어의 투사체가 몬스터와 충돌했는지 확인
    virtual bool        hasCollideWithMonster();
    // @brief 몬스터의 투사체가 플레이어와 충돌했는지 확인
    bool                hasCollideWithPlayer();
    // @brief 탄이 이동한 거리가 range를 넘었는지 확인
    bool                hasTraveledTooFar() const;
    // @brief 탄의 관통횟수가 전부 소모되었는지 확인
    bool                hasPenetration() const { return penetration <= 0; }

    virtual void       AfterEffect();
};


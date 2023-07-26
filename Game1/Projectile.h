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

    Vector2         dir;                    // ����
    float           speed;                  // �ӵ�
    int             damage;                 // ���ݷ�
    int             penetration;            // �����
    float           range;                  // �����Ÿ�
    float           shove;                  // ���ĳ��� ���
    float           traveledDistance;       // �̵��Ÿ�

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
    /* ź�� �̵��� �Ÿ��� range�� �Ѿ����� Ȯ�� */
    bool                hasTraveledTooFar() const;
    /* ź�� ����Ƚ���� ���� �Ҹ�Ǿ����� Ȯ�� */
    bool                hasPenetration() const { return penetration <= 0; }

    virtual void       AfterEffect();
};


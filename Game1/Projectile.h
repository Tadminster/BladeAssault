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

    Projectile() = default;
    // @brief �߻�ü ������
    // @param spawnPos �߻�ü ������
    // @param spawnPos �߻�ü ���� ��ġ
    // @param dir �߻�ü ����
    // @param speed �߻�ü �ӵ�
    // @param range �߻�ü �����Ÿ�
    // @param damage �߻�ü ������
    // @param penetration �����
    Projectile(float scale, Vector2 spawnPos, Vector2 dir, float speed, float range, float damage, int penetration);
    Projectile(Vector2 spawnPos, Vector2 dir, float speed, float range, float damage, int penetration);
    ~Projectile();  
    virtual void        Update();
    virtual void        Render();

    // @brief �÷��̾��� ����ü�� ���Ϳ� �浹�ߴ��� Ȯ��
    virtual bool        hasCollideWithMonster();
    // @brief ������ ����ü�� �÷��̾�� �浹�ߴ��� Ȯ��
    bool                hasCollideWithPlayer();
    // @brief ź�� �̵��� �Ÿ��� range�� �Ѿ����� Ȯ��
    bool                hasTraveledTooFar() const;
    // @brief ź�� ����Ƚ���� ���� �Ҹ�Ǿ����� Ȯ��
    bool                hasPenetration() const { return penetration <= 0; }

    virtual void       AfterEffect();
};


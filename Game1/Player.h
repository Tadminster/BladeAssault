#pragma once
#include "Item.h"

// @brief		��� �÷��̾� ĳ������ �θ� Ŭ����
class Player : public Creature
{
protected:
	ObImage* charging;
	ObImage* skill;
	ObImage* crouch;
	ObImage* dash;
	ObImage* damaged;
	ObImage* die;


	//PlayerState PrevState;
	//PlayerState	CurrentState;

	Vector2		lastDir;
	Vector2		dashTargetPos;

	vector<class Projectile*>	projectiles;

	int			mp;
	int			maxMp;

	//ATTACK
	float		damageScale;				// ��� ���ݷ� ������
	float		normalDamageScale;			// �Ϲ� ���ݷ� ������
	float		skillDamageScale;			// ��ų ���ݷ� ������
	float		chargingDamageScale;		// ��¡ ���ݷ� ������
	float		chargingTimeScale;			// ��¡ �ð� ������
	float		fullLifeDamageScale;		// ü���� 100%�� �� ���ݷ� ������

	//DEFENCE
	float 		damageRedution;				// ���� ����

	//CHARGING
	float		chargingTime;				// ���� �ð�
	float		chargingTimeMax;			// ���� �ִ� �ð�
	int			chargingStartFrame;			// ���� ���� ������
	int			chargingEndFrame;			// ���� ���� ������

	//SKILL
	float		skillRemainingCooldown;		// ���� ���� ���ð�
	float		skillCooldown;				// ��ų ��� ������ ���� ���ð�
	float		skillCooldownScale;			// ��ų ���� ���ð� ���ҷ�
	int			skillManaCost;				// ��ų ���� �Ҹ�Ǵ� ����

	//JUMP
	int			jumpCount;					// ���� Ƚ��
	int			jumpCountMax;				// ���� �ִ� Ƚ��

	//DASH
	float		dashWeight;					// �뽬 ����ġ
	float		dashRemainingCooldown;		// ���� ���� ���ð�
	float		dashCooldown;				// �뽬 ��� ������ ���� ���ð�
	float		dashCooldownScale;			// �뽬 ���� ���ð� ���ҷ�

	//ETC
	float		timeOfDamaged;				// �ǰݴ��� �ð� ��Ͽ�
    int			criticalChance;				// ũ��Ƽ�� Ȯ��
	float		criticalDamage;				// ũ��Ƽ�� ������ ����

public:
	bool		isFullLife;					// �ִ� ü���� ������ ����
	bool		isLowLife;					// ���� ü���� ������ ����
	bool		isLowLifeNoManaCost;		// ���� ü���� �� ��ų ���� ���� �Ҹ� ������ ����
	bool		isCharging;					// ��¡ ������ ����
	bool		damageTaken;				// �ǰݴ��ߴ��� ����(�ǰ�FX ��¿�)

public:
	Player();
	virtual ~Player();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void Control();
	virtual void Attack() override;
	virtual void Skill();
	virtual void Charging();
	virtual void ChargingAttack();
	virtual void SkillAttack();
	virtual void Dash();
	virtual void activateItem(Item* item);

	void actionsWhenDamaged(float damage);

	// Get
	int		GetMp() { return mp; }
	int		GetMaxMp() { return maxMp; }
	float	GetDashCooldown() { return dashRemainingCooldown;  }
	float	GetSkillCooldown() { return skillRemainingCooldown; }
	bool	hasEnoughManaForSkill() { return mp >= skillManaCost; }
	Vector2 GetPosition() { return collider->GetWorldPos(); }
	ObRect* GetCollider() { return collider; }

	// Set
	void	SetPosition(Vector2 position) { collider->SetWorldPos(position); }
};
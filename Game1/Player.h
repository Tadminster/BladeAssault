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

	Vector2		lastDir;
	Vector2		dashTargetPos;

	vector<class Projectile*>	projectiles;

	
	float		secTimer				= 0.0f;		// �ʴ� ����� ����	Ÿ�̸�

	int			mp;
	int			maxMp;

	//ATTACK
	float		damageScale				= 1.0f;		// ��� ���ݷ� ������
	float		normalDamageScale		= 1.0f;		// �Ϲ� ���ݷ� ������
	float		skillDamageScale		= 1.0f;		// ��ų ���ݷ� ������
	float		chargingDamageScale		= 1.0f;		// ��¡ ���ݷ� ������
	float		chargingTimeScale		= 1.0f;		// ��¡ �ð� ������
	float		fullLifeDamageScale		= 1.0f;		// ü���� 100% �� �� ���ݷ� ������
	float		lowLifeDamageScale		= 1.0f;		// ü���� 30% ������ �� ���ݷ� ������

    int			criticalChance			= 0.1f;		// ũ��Ƽ�� Ȯ��
	float		criticalDamage			= 1.5f;		// ũ��Ƽ�� ������ ����

	//DEFENCE
	float 		damageRedution			= 1.0f;		// ���� ����
	int			dodgeChance				= 5;		// ȸ����

	//CHARGING
	float		chargingTime			= 0.0f;		// ���� �ð�
	float		chargingTimeMax			= 3.0f;		// ���� �ִ� �ð�
	int			chargingStartFrame;					// ���� ���� ������	(�ڽĿ��� �ʱ�ȭ)
	int			chargingEndFrame;					// ���� ���� ������ (�ڽĿ��� �ʱ�ȭ)

	//SKILL
	float		skillRemainingCooldown;				// ���� ���� ���ð� (�ڽĿ��� �ʱ�ȭ)
	float		skillCooldown;						// ��ų ��� ������ ���� ���ð� (�ڽĿ��� �ʱ�ȭ)
	float		skillCooldownScale;					// ��ų ���� ���ð� ���ҷ� (�ڽĿ��� �ʱ�ȭ)
	int			skillManaCost;						// ��ų ���� �Ҹ�Ǵ� ���� (�ڽĿ��� �ʱ�ȭ)

	//MOVE
	float		moveSpeedScale			= 1.0f;		// �̵� �ӵ� ������

	//JUMP
	int			jumpCount				= 0;		// ���� Ƚ��
	int			jumpCountMax			= 2;		// ���� �ִ� Ƚ��

	//DASH
	float		dashWeight				= 0.0f;		// �뽬 ����ġ
	float		dashRemainingCooldown	= 0.0f;		// ���� ���� ���ð�
	float		dashCooldown			= 2.0f;		// �뽬 ��� ������ ���� ���ð�
	float		dashCooldownScale;					// �뽬 ���� ���ð� ���ҷ�

	//ETC
	float		timeOfDamaged			= 0.0f;		// �ǰݴ��� �ð� ��Ͽ�

public:
	bool		isFullLife				= true;		// �ִ� ü���� ������ ����
	bool		isLowLife				= false;	// ���� ü���� ������ ����
	bool		isCharging				= false;	// ��¡ ������ ����
	bool		damageTaken				= false;	// �ǰݴ��ߴ��� ����(�ǰ�FX ��¿�)

	// ITEM
	bool		hasCandle				= false;	// ĵ�� ���� ���� (���� ü���� �� ��ų ���� ���� �Ҹ� ����)
	bool		hasFirstAidKit			= false;	// ���޻��� ���� ���� (���� ü���� �� HP ���)
	bool		hasCactus				= false;	// ������ ���� ���� (�ǰݽ� ������ �ݻ�)
	bool		hasSyringe				= false;	// �ֻ�� ���� ���� (�ǰݽ� HP ���)
	bool		hasHeatedClub			= false;	// ����Ŭ�� ���� ���� (���� ü���� �� ������ ����)

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
	void DamageReflection(float damage);

	// Get
	int		GetMp()					{ return mp; }
	int		GetMaxMp()				{ return maxMp; }
	float	GetDashCooldown()		{ return dashRemainingCooldown;  }
	float	GetSkillCooldown()		{ return skillRemainingCooldown; }
	bool	hasEnoughManaForSkill() { return mp >= skillManaCost; }
	Vector2 GetPosition()			{ return collider->GetWorldPos(); }
	ObRect* GetCollider()			{ return collider; }

	// Set
	void	SetPosition(Vector2 position) { collider->SetWorldPos(position); }
};
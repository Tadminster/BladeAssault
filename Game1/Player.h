#pragma once

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

	//CHARGING
	float		chargingTime;				// ���� �ð�
	float		chargingTimeMax;			// ���� �ִ� �ð�
	int			chargingStartFrame;			// ���� ���� ������
	int			chargingEndFrame;			// ���� ���� ������

	//SKILL
	float		skillRemainingCooldown;		// ���� ���� ���ð�
	float		skillCooldown;				// ��ų ��� ������ ���� ���ð�
	int			skillManaCost;					// ��ų ���� �Ҹ�Ǵ� ����

	//JUMP
	int			jumpCount;					// ���� Ƚ��
	int			jumpCountMax;				// ���� �ִ� Ƚ��

	//DASH
	float		dashRemainingCooldown;		// ���� ���� ���ð�
	float		dashCooldown;				// �뽬 ��� ������ ���� ���ð�

	//ETC
	float		timeOfDamaged;				// �ǰݴ��� �ð� ��Ͽ�

public:
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

	void actionsWhenDamaged(int value);

	// Get
	int		GetMp() { return mp; }
	int		GetMaxMp() { return maxMp; }
	float	GetDashCooldown() { return dashRemainingCooldown;  }
	float	GetSkillCooldown() { return skillRemainingCooldown; }
	bool	hasEnoughManaForSkill() { return mp >= skillManaCost; }

	// Set
	void	SetPosition(Vector2 position) { collider->SetWorldPos(position); }
};
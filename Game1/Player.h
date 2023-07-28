#pragma once

// @brief		모든 플레이어 캐릭터의 부모 클래스
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
	float		chargingTime;				// 충전 시간
	float		chargingTimeMax;			// 충전 최대 시간
	int			chargingStartFrame;			// 충전 시작 프레임
	int			chargingEndFrame;			// 충전 종료 프레임

	//SKILL
	float		skillRemainingCooldown;		// 남은 재사용 대기시간
	float		skillCooldown;				// 스킬 사용 직후의 재사용 대기시간
	int			skillManaCost;					// 스킬 사용시 소모되는 마나

	//JUMP
	int			jumpCount;					// 점프 횟수
	int			jumpCountMax;				// 점프 최대 횟수

	//DASH
	float		dashRemainingCooldown;		// 남은 재사용 대기시간
	float		dashCooldown;				// 대쉬 사용 직후의 재사용 대기시간

	//ETC
	float		timeOfDamaged;				// 피격당한 시간 기록용

public:
	bool		isCharging;					// 차징 중인지 여부
	bool		damageTaken;				// 피격당했는지 여부(피격FX 출력용)

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
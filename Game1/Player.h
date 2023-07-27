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

	float		chargingTime;
	float		chargingTimeMax;
	int			chargingStartFrame;
	int			chargingEndFrame;

	int			jumpCount;
	int			jumpCountMax;
	float		dashCooldown;
	float		dashDealay;

	float		timeOfDamaged;

public:
	bool		isCharging;
	bool		damageTaken;

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
	virtual void Dash();

	void actionsWhenDamaged(int value);

	// Get
	int		GetMp() { return mp; }
	int		GetMaxMp() { return maxMp; }
	float	GetDashCooldown() { return dashCooldown;  }

	// Set
	void	SetPosition(Vector2 position) { collider->SetWorldPos(position); }
};
#pragma once
//enum class PlayerState
//{
//	IDLE,
//	RUN,
//	DASH,
//	JUMP,
//	CROUCH,
//	CROUCH_DOWN,
//	ATTACK,
//	DAMAGED,
//	DIE
//};

class Player : public Creature
{
protected:

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

	int			jumpCount;
	int			jumpCountMax;
	float		dashCooldown;
	float		dashDealay;

	float		timeOfDamaged;

public:
	bool		damageTaken;

public:
	Player();
	virtual ~Player();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void Control();
	virtual void Attack() override;
	virtual void Dash();

	void actionsWhenDamaged(int value);

	// Get
	int		GetMp() { return mp; }
	int		GetMaxMp() { return maxMp; }
	float	GetDashCooldown() { return dashCooldown;  }

	// Set
	void	SetPosition(Vector2 position) { collider->SetWorldPos(position); }
};
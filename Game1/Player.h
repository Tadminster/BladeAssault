#pragma once
enum class PlayerState
{
	IDLE,
	RUN,
	DASH,
	JUMP,
	CROUCH,
	CROUCH_DOWN,
	ATTACK
};

class Player
{
protected:
	ObRect* collider;
	ObImage* idle;
	ObImage* run;
	ObImage* jump;
	ObImage* crouch;
	ObImage* attack;
	ObImage* dash;

	PlayerState  PrevState;
	PlayerState  Currentstate;
	Vector2		dir;
	Vector2		lastPos;
	Vector2		lastDir;
	Vector2		dashTargetPos;


	vector<class Projectile*>	projectiles;


	int			HP;
	int			MaxHP;
	int			MP;
	int			MaxMP;
	int			AttackDamage;
	int			AttackRange;
	int			AttackSpeed;
	int			Defence;

	float		speed;

	float		jumpSpeed;
	float		jumpTime;
	int			jumpCount;
	int			jumpCountMax;

	float		dashCooldown;
	float		dashDealay;



public:
	float		gravity;
	bool		onFloor;
	bool		onWall;
	bool		onWallSlide;
	bool		isLanding;

public:
	Player();
	virtual ~Player();
	virtual void Init();
	virtual void Update();
	virtual void Render();
	void GoBack();
	virtual void Control();
	virtual void Attack();
	virtual void Dash();
	virtual	void Jump();
	void OnFloorAction();
	void OnWallAction();
	void OnWallSlideAction();


	// Get
	PlayerState GetState() { return Currentstate; }
	ObRect* GetCollider() { return collider; };
	Vector2 GetFoot();
	Vector2 GetHead();
	Vector2 GetDirection() { return dir; }

	// Set
	void	SetPosition(Vector2 position) { collider->SetWorldPos(position); }
};
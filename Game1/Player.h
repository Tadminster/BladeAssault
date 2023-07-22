#pragma once
enum class PlayerState
{
	IDLE,
	RUN,
	DASH,
	JUMP,
	CROUCH,
	CROUCH_DOWN,
	ATTACK,
	DAMAGED
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
	ObImage* damaged;
	ObImage* shadow;

	PlayerState PrevState;
	PlayerState	CurrentState;

	Vector2		dir;
	Vector2		lastPos;
	Vector2		lastDir;
	Vector2		dashTargetPos;

	vector<class Projectile*>	projectiles;


	int			hp;
	int			maxHP;
	int			mp;
	int			maxMP;
	int			attackDamage;
	int			attackRange;
	int			attackSpeed;
	int			defence;

	float		speed;

	float		jumpSpeed;
	float		jumpTime;
	int			jumpCount;
	int			jumpCountMax;

	float		dashCooldown;
	float		dashDealay;

	float		timeOfDamaged;


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

	// 특정 상황에서의 액션
	void OnFloorAction();
	void OnWallAction();
	void OnWallSlideAction();

	void actionsWhenDamaged(int value);

	// Get
	PlayerState GetState() { return CurrentState; }
	ObRect* GetCollider() { return collider; };
	Vector2 GetFoot();
	Vector2 GetHead();
	Vector2 GetDirection() { return dir; }

	// Set
	void	SetPosition(Vector2 position) { collider->SetWorldPos(position); }
};
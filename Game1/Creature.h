#pragma once
enum class State
{
	SPAWN,			// 0
	STANDBY,		// 1
	IDLE,			// 2
	RUN,			// 3
	DASH,			// 4
	JUMP,			// 5
	CROUCH,			// 6
	CROUCH_DOWN,	// 7
	ATTACK,			// 8
	CHARGING,		// 9
	SKILL,			// 10
	DAMAGED,		// 11
	DIE				// 12
};

// @brief		모든 생물의 부모 클래스
class Creature
{
protected:
	class ObRect* collider;
	class ObImage* idle;
	class ObImage* run;
	class ObImage* jump;
	class ObImage* attack;
	class ObImage* shadow;
	class ObImage* spawn;


	State		PrevState;
	State		CurrentState;

	int			hp;				// 체력
	int			maxHp;			// 최대체력

	int			damage;			// 공격력
	int			defence;		// 방어력
	int			attackRange;	// 사정거리 (최하위 자식클래스에서 정의)
	float		attackSpeed;	// 공격속도 (최하위 자식클래스에서 정의)
	float		moveSpeed;		// 이동속도 (최하위 자식클래스에서 정의)

	float		jumpTime;
	float		jumpSpeed;

	Vector2		dir;
	Vector2		lastPos;

public:
	float		gravity;
	bool		onFloor;
	bool		onWall;
	bool		onWallSide;
	bool		isLanding;

public:
	Creature();
	virtual ~Creature();
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual	void Jump();
	virtual void Attack();

	// 특정 상황에서의 액션
	void OnFloorAction();
	void OnWallAction();
	void OnWallSlideAction();

	// Get
	ObRect* GetCollider()	{ return collider; };
	State	GetState()		{ return CurrentState; }
	Vector2 GetDirection()	{ return dir; }
	Vector2 GetFoot();
	Vector2 GetHead();

	int		GetHp()			{ return hp; }
	int		GetMaxHp()		{ return maxHp; }

	// Set
	void    SetDirection(Vector2 direction) { dir = direction; }

	//
	void GoBack();
};


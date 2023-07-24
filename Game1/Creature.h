#pragma once
enum class State
{
	IDLE,
	RUN,
	DASH,
	JUMP,
	CROUCH,
	CROUCH_DOWN,
	ATTACK,
	DAMAGED,
	DIE
};

class Creature
{
protected:
	class ObRect* collider;
	class ObImage* idle;
	class ObImage* run;
	class ObImage* jump;
	class ObImage* attack;
	class ObImage* shadow;

	State		PrevState;
	State		CurrentState;

	int			hp;			// 체력
	int			maxHp;		// 최대체력

	int			damage;
	int			defence;
	int			attackSpeed;
	int			attackRange;
	float		moveSpeed;
	float		jumpSpeed;

	Vector2		dir;
	Vector2		lastPos;

public:
	float		gravity;
	bool		onFloor;
	bool		onWall;
	bool		onWallSlide;
	bool		isLanding;

public:
	Creature();
	~Creature();

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

	//
	void GoBack();
};


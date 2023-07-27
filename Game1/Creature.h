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

// @brief		��� ������ �θ� Ŭ����
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

	int			hp;			// ü��
	int			maxHp;		// �ִ�ü��

	int			damage;
	int			defence;
	int			attackRange;
	float		attackSpeed;
	float		moveSpeed;

	float		jumpTime;
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
	virtual void Init();
	virtual void Update();
	virtual void Render();

	virtual	void Jump();
	virtual void Attack();

	// Ư�� ��Ȳ������ �׼�
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


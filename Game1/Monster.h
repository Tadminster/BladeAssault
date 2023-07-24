#pragma once
enum class MonsterState
{
	IDLE,
	RUN,
	JUMP,
	ATTACK
};

enum class MonsterDamageTaken
{
	NORMAL,
	DAMAGED,
	IMMUNE
};

class Monster
{
protected:
	class ObRect*	collider;
	class ObImage*	idle;
	class ObImage*	run;
	class ObImage*	jump;
	class ObImage*	attack;
	class ObImage*	shadow;

	MonsterState		state;
	MonsterDamageTaken	dmgTaken;
	Vector2				dir;
	Vector2				lastPos;

	int		hp;						// 체력
	float	damage;					// 공격력
	float	speed;					// 이동속도

	float	knockBackFactor;		// 넉백에 사용되는 계수
	float	timeOfDamage;			// 데미지 받은 시간 기록

	float	attackSpeed;			// 공격속도
	int		attackFrame;			// 공격 프레임
	bool	realAttack;				// 실제 공격을 위한	bool

public:
	float		gravity;
	bool		onFloor;
	bool		onWall;
	bool		onWallSlide;
	bool		isLanding;

public:
	Monster();
	virtual ~Monster();
	virtual void Update();
	virtual void Render();

	virtual bool isAttackCooldown();
	virtual void Attack();

	// 특정 상황에서의 액션
	void OnFloorAction();
	void OnWallAction();
	void OnWallSlideAction();

	// Get
	virtual ObRect* GetCollider()	{ return collider; }
	MonsterState	GetState()		{ return state; }
	Vector2			GetFoot();
	Vector2			GetHead();
	int				GetHp()			{ return hp;  }


	bool isDead() const { return hp == 0; }
	void actionsWhenDamaged(Vector4 value);
	void GoBack();
	void knockBack();

};


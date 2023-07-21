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

	MonsterState		state;
	MonsterDamageTaken	dmgTaken;
	Vector2				dir;

	int		hp;						// 체력
	float	damage;					// 공격력
	float	speed;					// 이동속도

	float	knockBackFactor;		// 넉백에 사용되는 계수
	float	timeOfDamage;			// 데미지 받은 시간 기록

	float	attackSpeed;			// 공격속도
	int		attackFrame;			// 공격 프레임
	bool	realAttack;				// 실제 공격을 위한	bool

public:
	Monster();
	virtual ~Monster();
	virtual void Init(Vector2 spawnPos);
	virtual void Update();
	virtual void Render();

	virtual bool isAttackCooldown();
	virtual void Attack();

	// Get
	virtual ObRect* GetCollider()	{ return collider; }
	int				GetHp()			{ return hp;  }

	bool isDead() const { return hp == 0; }
	void actionsWhenDamaged(Vector4 value);
	void knockBack();
};


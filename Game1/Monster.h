#pragma once
enum class MonsterState
{
	IDLE,
	RUN,
	JUMP,
	ATTACK
};


class Monster
{
protected:
	class ObRect*	collider;
	class ObImage*	idle;
	class ObImage*	run;
	class ObImage*	jump;
	class ObImage*	attack;

	MonsterState	status;
	Vector2			dir;

	int		hp;						// 체력
	float	damage;					// 공격력
	//float	defence;				// 방어력
	float	attackSpeed;			// 공격속도
	float	speed;					// 이동속도

	float	knockBackFactor;		// 넉백에 사용되는 계수

	float	timeOfDamage;			// 데미지 받은 시간 기록

public:
	Monster();
	virtual ~Monster() {};
	virtual void Init();
	virtual void Update();
	virtual void Render();
};


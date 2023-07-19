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

	int		hp;						// ü��
	float	damage;					// ���ݷ�
	//float	defence;				// ����
	float	attackSpeed;			// ���ݼӵ�
	float	speed;					// �̵��ӵ�

	float	knockBackFactor;		// �˹鿡 ���Ǵ� ���

	float	timeOfDamage;			// ������ ���� �ð� ���

public:
	Monster();
	virtual ~Monster() {};
	virtual void Init();
	virtual void Update();
	virtual void Render();
};


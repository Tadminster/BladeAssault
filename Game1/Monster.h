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

	int		hp;						// ü��
	float	damage;					// ���ݷ�
	float	speed;					// �̵��ӵ�

	float	knockBackFactor;		// �˹鿡 ���Ǵ� ���
	float	timeOfDamage;			// ������ ���� �ð� ���

	float	attackSpeed;			// ���ݼӵ�
	int		attackFrame;			// ���� ������
	bool	realAttack;				// ���� ������ ����	bool

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


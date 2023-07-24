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

	int		hp;						// ü��
	float	damage;					// ���ݷ�
	float	speed;					// �̵��ӵ�

	float	knockBackFactor;		// �˹鿡 ���Ǵ� ���
	float	timeOfDamage;			// ������ ���� �ð� ���

	float	attackSpeed;			// ���ݼӵ�
	int		attackFrame;			// ���� ������
	bool	realAttack;				// ���� ������ ����	bool

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

	// Ư�� ��Ȳ������ �׼�
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


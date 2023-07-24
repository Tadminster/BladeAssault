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

class Monster : public Creature
{
protected:
	MonsterState		state;
	MonsterDamageTaken	dmgTaken;

	float	knockBackFactor;		// �˹鿡 ���Ǵ� ���
	float	timeOfDamage;			// ������ ���� �ð� ���

	int		attackFrame;			// ���� ������
	bool	realAttack;				// ���� ������ ����	bool

public:
	Monster();
	virtual ~Monster();
	virtual void Update();
	virtual void Render();

	virtual bool isAttackCooldown();
	virtual void Attack();

	// Get
	MonsterState	GetState()		{ return state; }


	bool isDead() const { return hp == 0; }
	void actionsWhenDamaged(Vector4 value);
	void knockBack();

};


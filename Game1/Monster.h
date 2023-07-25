#pragma once
enum class MonsterDamageTaken
{
	NORMAL,
	DAMAGED,
	IMMUNE
};

class Monster : public Creature
{
protected:
	MonsterDamageTaken	dmgTaken;

	float	knockBackFactor;		// �˹鿡 ���Ǵ� ���
	float	timeOfDamage;			// ������ ���� �ð� ���

	int		maxAttackDistance;		// ���� ������ �ִ� �Ÿ�
	int		attackFrame;			// ���� ������
	bool	realAttack;				// ���� ������ ����	bool

	float	lastAttackTime{0};		// ������ ���� �ð�
	float	timeTakenToAttackOnce;  // �ѹ� �����ϴµ� �ɸ��� �ð�

public:
	Monster();
	Monster(Vector2 spawnPos);
	virtual ~Monster();
	virtual void Update();
	virtual void Render();

	virtual bool isAttackCooldown();
	virtual void Attack();

	//
	bool isDead() const { return hp == 0; }
	void actionsWhenDamaged(Vector4 value);
	void knockBack();

};


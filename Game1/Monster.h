#pragma once
enum class MonsterDamageTaken
{
	NORMAL,
	DAMAGED,
	IMMUNE
};

// @brief		��� ������ �θ� Ŭ����
//				������ ����� �ൿ�� ����
class Monster : public Creature
{
protected:
	ObImage*			ui_frame_hp;
	ObImage*			ui_gauge_hp;

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

	// deep copy
	void operator=(Monster* monster);

	virtual ~Monster();
	virtual void Update();
	virtual void Render();

	virtual bool isAttackCooldown();
	virtual void Attack();

	//
	bool isDead() const; 
	void actionsWhenDamaged(int damage, int knockBackFactor, int criticalChance);
	void knockBack();



};


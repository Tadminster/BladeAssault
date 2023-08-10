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

	string  name;					// ���� �̸�

	float	knockBackFactor;		// �˹鿡 ���Ǵ� ���
	float	timeOfDamage;			// ������ ���� �ð� ���

	int		maxAttackDistance;		// ���� ������ �ִ� �Ÿ�
	int		attackFrame;			// ���� ������
	bool	realAttack;				// ���� ������ ����	bool

	float	lastAttackTime{ 0.0f };	// ������ ���� �ð�
	float	timeTakenToAttackOnce;  // �ѹ� �����ϴµ� �ɸ��� �ð� 

public:
	Monster();

	virtual ~Monster();
	virtual void Update();
	virtual void Render();

	virtual bool isAttackCooldown();
	virtual void Attack();

	//
	virtual	bool isDead() const; 
	void actionsWhenDamaged(int damage, int knockBackFactor, int criticalChance);
	void knockBack();

	string& GetName()		{ return name; }
	int		GetDamage()		{ return damage; }
	Vector2 GetPosition()	{ return collider->GetWorldPos(); }
};


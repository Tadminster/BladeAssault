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

	float	knockBackFactor;		// 넉백에 사용되는 계수
	float	timeOfDamage;			// 데미지 받은 시간 기록

	int		attackFrame;			// 공격 프레임
	bool	realAttack;				// 실제 공격을 위한	bool

public:
	Monster();
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


#pragma once
enum class MonsterDamageTaken
{
	NORMAL,
	DAMAGED,
	IMMUNE
};

// @brief		모든 몬스터의 부모 클래스
//				몬스터의 공통된 행동을 정의
class Monster : public Creature
{
protected:
	ObImage*			ui_frame_hp;
	ObImage*			ui_gauge_hp;

	MonsterDamageTaken	dmgTaken;

	string  name;					// 몬스터 이름

	float	knockBackFactor;		// 넉백에 사용되는 계수
	float	timeOfDamage;			// 데미지 받은 시간 기록

	int		maxAttackDistance;		// 공격 가능한 최대 거리
	int		attackFrame;			// 공격 프레임
	bool	realAttack;				// 실제 공격을 위한	bool

	float	lastAttackTime{ 0.0f };	// 마지막 공격 시간
	float	timeTakenToAttackOnce;  // 한번 공격하는데 걸리는 시간 

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


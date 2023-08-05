#pragma once
#include "Item.h"

// @brief		모든 플레이어 캐릭터의 부모 클래스
class Player : public Creature
{
protected:
	ObImage* charging;
	ObImage* skill;
	ObImage* crouch;
	ObImage* dash;
	ObImage* damaged;
	ObImage* die;

	Vector2		lastDir;
	Vector2		dashTargetPos;

	vector<class Projectile*>	projectiles;

	
	float		secTimer				= 0.0f;		// 초당 재생을 위한	타이머

	int			mp;
	int			maxMp;

	//ATTACK
	float		damageScale				= 1.0f;		// 모든 공격력 스케일
	float		normalDamageScale		= 1.0f;		// 일반 공격력 스케일
	float		skillDamageScale		= 1.0f;		// 스킬 공격력 스케일
	float		chargingDamageScale		= 1.0f;		// 차징 공격력 스케일
	float		chargingTimeScale		= 1.0f;		// 차징 시간 스케일
	float		fullLifeDamageScale		= 1.0f;		// 체력이 100% 일 때 공격력 스케일
	float		lowLifeDamageScale		= 1.0f;		// 체력이 30% 이하일 때 공격력 스케일

    int			criticalChance			= 0.1f;		// 크리티컬 확률
	float		criticalDamage			= 1.5f;		// 크리티컬 데미지 배율

	//DEFENCE
	float 		damageRedution			= 1.0f;		// 피해 감소
	int			dodgeChance				= 5;		// 회피율

	//CHARGING
	float		chargingTime			= 0.0f;		// 충전 시간
	float		chargingTimeMax			= 3.0f;		// 충전 최대 시간
	int			chargingStartFrame;					// 충전 시작 프레임	(자식에서 초기화)
	int			chargingEndFrame;					// 충전 종료 프레임 (자식에서 초기화)

	//SKILL
	float		skillRemainingCooldown;				// 남은 재사용 대기시간 (자식에서 초기화)
	float		skillCooldown;						// 스킬 사용 직후의 재사용 대기시간 (자식에서 초기화)
	float		skillCooldownScale;					// 스킬 재사용 대기시간 감소량 (자식에서 초기화)
	int			skillManaCost;						// 스킬 사용시 소모되는 마나 (자식에서 초기화)

	//MOVE
	float		moveSpeedScale			= 1.0f;		// 이동 속도 스케일

	//JUMP
	int			jumpCount				= 0;		// 점프 횟수
	int			jumpCountMax			= 2;		// 점프 최대 횟수

	//DASH
	float		dashWeight				= 0.0f;		// 대쉬 가중치
	float		dashRemainingCooldown	= 0.0f;		// 남은 재사용 대기시간
	float		dashCooldown			= 2.0f;		// 대쉬 사용 직후의 재사용 대기시간
	float		dashCooldownScale;					// 대쉬 재사용 대기시간 감소량

	//ETC
	float		timeOfDamaged			= 0.0f;		// 피격당한 시간 기록용

public:
	bool		isFullLife				= true;		// 최대 체력일 때인지 여부
	bool		isLowLife				= false;	// 낮은 체력일 때인지 여부
	bool		isCharging				= false;	// 차징 중인지 여부
	bool		damageTaken				= false;	// 피격당했는지 여부(피격FX 출력용)

	// ITEM
	bool		hasCandle				= false;	// 캔들 소유 여부 (낮은 체력일 때 스킬 사용시 마나 소모가 없음)
	bool		hasFirstAidKit			= false;	// 구급상자 소유 여부 (낮은 체력일 때 HP 재생)
	bool		hasCactus				= false;	// 선인장 소유 여부 (피격시 데미지 반사)
	bool		hasSyringe				= false;	// 주사기 소유 여부 (피격시 HP 재생)
	bool		hasHeatedClub			= false;	// 히팅클럽 소유 여부 (낮은 체력일 때 데미지 증가)

public:
	Player();
	virtual ~Player();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void Control();
	virtual void Attack() override;
	virtual void Skill();
	virtual void Charging();
	virtual void ChargingAttack();
	virtual void SkillAttack();
	virtual void Dash();
	virtual void activateItem(Item* item);

	void actionsWhenDamaged(float damage);
	void DamageReflection(float damage);

	// Get
	int		GetMp()					{ return mp; }
	int		GetMaxMp()				{ return maxMp; }
	float	GetDashCooldown()		{ return dashRemainingCooldown;  }
	float	GetSkillCooldown()		{ return skillRemainingCooldown; }
	bool	hasEnoughManaForSkill() { return mp >= skillManaCost; }
	Vector2 GetPosition()			{ return collider->GetWorldPos(); }
	ObRect* GetCollider()			{ return collider; }

	// Set
	void	SetPosition(Vector2 position) { collider->SetWorldPos(position); }
};